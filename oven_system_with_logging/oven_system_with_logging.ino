#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// SD card setup
const int SDcardPin = 2;    // CS pin for SD card
bool SDpresent = false;     // Stores if an SD card was present at initialization
String filename;            // Stores the datafile name for the run
//File logfile;               // File used

// A4 is SDA
// A5 is SCL

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

// Keypad config
const int row1 = 6; // Row 1 pin
const int row2 = 5;
const int row3 = 4;
const int row4 = 3;
const int col1 = 10; // Column 1 pin
const int col2 = 9;
const int col3 = 8;
const int col4 = 7;
// Keypad works by detecting the intersection of a row and col pulling down an input. (A column pulling the row down)

const int heater = 14;  // Heater relay pin
bool heaterState;       // State variable

// Control variables
int screen, field;                  // Used for display
const int numScreens = 4;           // Used as a limit for number of distinct screens
const int numFields = 3;            // Used as a limit for number of fields on a screen

const int maxFieldLength = 6;        // Max length of entered data
String fields[9];                    // Used to display entry data (should have numFields * numScreens elements)

int stage = 1;                          // Records cooking stage
double targetTemp, curTemp;              // Target and current temp
double temperature[5];                   // Used to store temp set points
const float tempTol = 5;                // Used as tolerance for over temp - IMPORTANT
unsigned long setPointTimes[5];         // Used for changes
double elapsedTime;                      // Used for status display
String endTime;                         // Used for status display (to minimize repeated instructions)

// Temperature probes
const int tempPin[] = {A7, A3};                     // Stores probes pins
const double setResis[] = {9960, 9830};             // Stores set resistor values
const double R25[] = {125000.0, 125000.0};          // Stores the calibration value of each NTC
// REMEMBER TO USE KELVIN
const double T25[] = {0.0034411562284928, 0.0034411562284928};  // Stores the reciprical (^-1) of the calibration temperature in K

const int numPorts = 2;                        // Number of ports for probes
int numProbes = 0;                                // Stores number of connected probes
bool connectedProbes[] = {false, false};   // Stores which probes are connected

void setup() {
  // Serial.begin(9600); // For debugging
  
  lcd.begin(20, 4);   // Set up display. 20 character in 4 rows
  lcd.clear();        //Clear the display
  
  // Keypad setup
  pinMode(row1, INPUT_PULLUP); pinMode(row2, INPUT_PULLUP); pinMode(row3, INPUT_PULLUP); pinMode(row4, INPUT_PULLUP);
  pinMode(col1, OUTPUT); pinMode(col2, OUTPUT); pinMode(col3, OUTPUT); pinMode(col4, OUTPUT);

  pinMode(heater, OUTPUT);            // Controls relay
  heaterState = LOW;                  // Off by default
  digitalWrite(heater, heaterState);

  // Probe setup
  for (int i = 0; i < numPorts; i++) {
//    //Serial verification
//    Serial.print(tempPin[i]);
//    Serial.print('\t');
//    Serial.println(analogRead(tempPin[i]));
    if (analogRead(tempPin[i]) > 10) {
      numProbes++;                // Increment number of probes
      connectedProbes[i] = true;  // Record it's presence
    }
  }
  if (numProbes == 0) {
    // Alert them if no probes detected
    printCenter(0, F("!!!!!!!!!!!!!!!!!!!!"));
    printCenter(1, F("!  NO TEMP PROBES  !"));
    printCenter(2, F("!     DETECTED     !")); 
    printCenter(3, F("!!!!!!!!!!!!!!!!!!!!"));
    delay(600000);
  }

  // SD card setup
  pinMode(SDcardPin, OUTPUT);
  SDpresent = SD.begin(SDcardPin);  // Record presence
  if (SDpresent) {
    // Finds filename to use, to not overwrite previous logs
    int runNum = 0; // Used to record run number
    while (SD.exists("oven" + String(runNum) + ".csv")) {
      runNum++; // Increments
    }
    filename = "oven" + String(runNum) + ".csv";    // Records filename

  }
  else {
    // Warn them
    printCenter(0, F("!!!!!!!!!!!!!!!!!!!!"));
    printCenter(1, F("! NO SD CARD FOUND !"));
    printCenter(2, F("!  ERGO NO LOGGING !")); 
    printCenter(3, F("!!!!!!!!!!!!!!!!!!!!"));
    delay(60000);
  }
  
  // Splash screen
  printCenter(1, F("Oven Control System"));
  printCenter(2, F("Designed for HPDVT"));
  delay(2000);                            // LOOK AT THE SPLASH SCREEN!!
  lcd.clear();

  // Status screen
  printCenter(0, F("Oven Configuration"));
  printLeft(1, F("Probes found:"));
  printLeft(2, F("SD Status:"));

  String temp = "";
  for (int i = 0; i < numPorts; i++) {
     if (connectedProbes[i]) temp += String(i + 1) + ","; // Lists probes
  }
  printRight(1, temp);       // Prints indexes of probes found
  if (SDpresent) printRight(2, F("Ready"));  // SD status
  else printRight(2, F("MISSING"));
  delay(5000);                           // Time to read
  lcd.clear();
  
  // Initialization
  screen = 0;
  field = 0;
}

void loop() {
  // Screen
  switch (screen) {
    case 0: // Setup first point
      printLeft(0, F("Target Temp"));
      printLeft(1, F("Rise Rt. c/m"));
      printLeft(2, F("Hold Time (m)"));
      printCenter(3, F("Stg 1"));
      printCursor();
      for (int i = 0; i < numFields; i++) {
        printRight(i, fields[i + numFields * screen]);
      }
      printRight(3, F("Stg 2>"));

      buttonAction(); // Performs button action
      break;
    case 1: // Second point config
      printLeft(0, F("Target Temp"));
      printLeft(1, F("Rise Rt. c/m"));
      printLeft(2, F("Hold Time (m)"));
      printLeft(3, F("<Stg 1"));
      printCenter(3, F("Stg 2"));
      printCursor();
      for (int i = 0; i < numFields; i++) {
        printRight(i, fields[i + numFields * screen]);
      }
      printRight(3, F("Strt>"));

      buttonAction(); // Performs button action

      // Check if starting oven
      if (screen == (numScreens - 2)) {
        stage = 1; // Entered first stage
        
        //Sets temperature points
        temperature[0] = currentTemp(); // Record starting temp
        temperature[1] = fields[0].toFloat();
        temperature[2] = temperature[1];
        temperature[3] = fields[numFields].toFloat();
        temperature[4] = temperature[3];

        // Gets times
        // Times are (target - start) / ramp rate
        elapsedTime = 0;
        setPointTimes[0] = millis();                                                          // Start time
        setPointTimes[1] = (temperature[1] - temperature[0]) * 60000 / fields[1].toFloat();   // Uses rate and difference to find ramp time
        setPointTimes[2] = fields[2].toFloat() * 60000;                                       // Records hold time
        setPointTimes[3] = (temperature[3] - temperature[2]) * 60000 / fields[1].toFloat();   // Second ramp
        setPointTimes[4] = fields[2 + numFields].toFloat() * 60000;                           // Last hold

        for (int i = 1; i <= 4; i++) {
          setPointTimes[i] += setPointTimes[i - 1]; //Makes the times cummulative
        }
        endTime = int(ceil((setPointTimes[4] - setPointTimes[0]) / 60000)); // Records the end as a string for status display
        
        if (SDpresent) recordConfig(); // Record config if possible
      }
      break;
      
    case 2: // Runtime
      // Control
      // Gets linearly interpolated temperature based on time and bounding set points
      // map() outputs long int, needed floats so I adjusted their source code
      targetTemp = (millis() - setPointTimes[stage - 1]) * (temperature[stage] - temperature[stage - 1]);
      targetTemp /= (setPointTimes[stage] - setPointTimes[stage - 1]);
      targetTemp += temperature[stage - 1];
      curTemp = currentTemp(); // Gets current temp

      if (curTemp < targetTemp) {
        heaterState = HIGH;                   // Too cold
        digitalWrite(heater, heaterState);
      }
      else if (curTemp > (targetTemp + 1)) {
        heaterState = LOW;                    // Too hot
        digitalWrite(heater, heaterState);
      }
      
      // Time
      if (millis() > setPointTimes[stage]) stage++; // Checks if approriate stage
      elapsedTime = millis() - setPointTimes[0];    // Elaplsed time in ms
      elapsedTime /= 60000;                         // Elapsed time in minutes
      
      // Screen stuff
      printLeft(0, F("Cur/Tar"));
      printLeft(1, F("Elp/End"));
      printLeft(2, F("Heater"));
      printCenter(3, F("Oven Status"));

      // Fields
      fields[numFields * screen] = F("  ");
      fields[numFields * screen] += String(curTemp, 1);       // Temp
      fields[numFields * screen] += F("/");
      fields[numFields * screen] += String(targetTemp, 1);   // Target

      fields[1 + numFields * screen] = String(elapsedTime, 0);   // Time
      fields[1 + numFields * screen] += F("/");
      fields[1 + numFields * screen] += endTime;                  // End

      if (heaterState) {
        fields[2 + numFields * screen] = " ON";  // Heater ON
      }
      else {
        fields[2 + numFields * screen] = "OFF"; // Heater OFF
      }

      for (int i = 0; i < numFields; i++) {
        printRight(i, fields[i + numFields * screen]);
      }

      // Check for finish (past stage 4)
      if (stage == 5) {
        screen++; // Go to next step
        lcd.clear();
        
        // Turn off heater
        heaterState = LOW;                  
        digitalWrite(heater, heaterState);
      }

      if (SDpresent) logData();  // Log data if possible
      delay(300); // Extending cycle time during run time
      break;
      
    case 3: // Finished
      printCenter(0, F("Process Complete"));
      printCenter(1, F("Oven is disabled"));
      printLeft(3, F("Cur. Temp"));
      printRight(3, "   " + String(currentTemp(), 1));

      delay(1000);
      break;
  }

  delay(25);
}

void printCenter(int row, String message) {
  int pos = 10 - (message.length() + 1) / 2; // Finds start to center message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printRight(int row, String message) {
  int pos = 20 - message.length(); // Finds start to right justify the message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printLeft(int row, String message) {
  lcd.setCursor(0, row);
  lcd.print(message);
}
void printCursor() {
  lcd.setCursor(19 - maxFieldLength, field);
  lcd.print('>');
}
