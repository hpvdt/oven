#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// A4 is SDA
// A5 is SCL

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

// Keypad config
const int row1 = 8; // Row 1 pin
const int row2 = 7;
const int row3 = 6;
const int row4 = 5;
const int col1 = 12; // Column 1 pin
const int col2 = 11;
const int col3 = 10;
const int col4 = 9;
char buttonPressed;
// Keypad works by detecting the intersection of a row and col pulling down an input. (A column pulling the row down)

const int heater = 2;  // Heater relay pin
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
const double tempTol = 5;                // Used as tolerance for over temp - IMPORTANT
unsigned long setPointTimes[5];         // Used for changes
double elapsedTime;                      // Used for status display
String endTime;                         // Used for status display (to minimize repeated instructions)

// Temperature probes
const int tempPin[] = {14};
const double setResis[] = {10000.0}; // Stores set resistor values
const double R25[] = {100000.0}; // Stores the calibration value of each NTC
const double T25[] = {0.0033557047}; // Stores the reciprical (^-1) of the calibration temperature in K

void setup() {
  lcd.begin(20, 4);   // Set up display. 20 character in 4 rows
  lcd.clear();        //Clear the display

  // Keypad setup
  pinMode(row1, INPUT_PULLUP); pinMode(row2, INPUT_PULLUP); pinMode(row3, INPUT_PULLUP); pinMode(row4, INPUT_PULLUP);
  pinMode(col1, OUTPUT); pinMode(col2, OUTPUT); pinMode(col3, OUTPUT); pinMode(col4, OUTPUT);

  pinMode(heater, OUTPUT);            // Controls relay
  heaterState = LOW;                  // Off by default
  digitalWrite(heater, heaterState);

  // Splash screen
  printCenter(1, "Oven Control System");
  printCenter(2, "Designed for HPDVT");
  delay(1000);
  lcd.clear();

  // Initialization
  screen = 0;
  field = 0;
}

void loop() {
  // Screen
  switch (screen) {
    case 0: // Setup first point
      printLeft(0, "Target Temp");
      printLeft(1, "Rise Rt. c/m");
      printLeft(2, "Hold Time (m)");
      printCenter(3, "Stg 1");
      printCursor();
      for (int i = 0; i < numFields; i++) {
        printRight(i, fields[i + numFields * screen]);
      }
      printRight(3, "Stg 2>");

      buttonAction(); // Performs button action
      break;
    case 1: // Second point config
      printLeft(0, "Target Temp");
      printLeft(1, "Rise Rt. c/m");
      printLeft(2, "Hold Time (m)");
      printLeft(3, "<Stg 1");
      printCenter(3, "Stg 2");
      printCursor();
      for (int i = 0; i < numFields; i++) {
        printRight(i, fields[i + numFields * screen]);
      }
      printRight(3, "Strt>");

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
      printLeft(0, "Cur/Tar");
      printLeft(1, "Elp/End");
      printLeft(2, "Heater");
      printCenter(3, "Oven Status");

      // Fields
      fields[numFields * screen] = "  ";
      fields[numFields * screen] += oneDecimal(curTemp);       // Temp
      fields[numFields * screen] += "/";
      fields[numFields * screen] += oneDecimal(targetTemp);   // Target

      fields[1 + numFields * screen] = oneDecimal(elapsedTime);   // Time
      fields[1 + numFields * screen] += "/";
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
      delay(300); // Extending cycle time during run time
      break;
      
    case 3: // Finished
      printCenter(0, "Process Complete");
      printCenter(1, "Oven is disabled");
      printLeft(3, "Cur. Temp");
      printRight(3, "   " + oneDecimal(currentTemp()));

      delay(1000);
      break;
  }

  delay(25);
}

// Checks keypad for what button is pressed (returns 'x' if nothing pressed)
char checkKeypad() {
  bool teststate = LOW; // Are we looking for highs or lows?

  char button = 'x'; // Stores button pressed (x will return if nothing pressed)

  digitalWrite(col1, teststate);
  digitalWrite(col2, !teststate);
  digitalWrite(col3, !teststate);
  digitalWrite(col4, !teststate);

  if (teststate == digitalRead(row1)) button = '1';
  if (teststate == digitalRead(row2)) button = '4';
  if (teststate == digitalRead(row3)) button = '7';
  if (teststate == digitalRead(row4)) button = '*';
  waitForRelease(teststate); // Wait for release
  digitalWrite(col1, !teststate);
  digitalWrite(col2, teststate);
  delay(1); // Delay to avoid transients

  if (teststate == digitalRead(row1)) button = '2';
  if (teststate == digitalRead(row2)) button = '5';
  if (teststate == digitalRead(row3)) button = '8';
  if (teststate == digitalRead(row4)) button = '0';
  waitForRelease(teststate); // Wait for release
  digitalWrite(col2, !teststate);
  digitalWrite(col3, teststate);
  delay(1); // Delay to avoid transients

  if (teststate == digitalRead(row1)) button = '3';
  if (teststate == digitalRead(row2)) button = '6';
  if (teststate == digitalRead(row3)) button = '9';
  if (teststate == digitalRead(row4)) button = '#';
  waitForRelease(teststate); // Wait for release
  digitalWrite(col3, !teststate);
  digitalWrite(col4, teststate);
  delay(1); // Delay to avoid transients

  if (teststate == digitalRead(row1)) button = 'A';
  if (teststate == digitalRead(row2)) button = 'B';
  if (teststate == digitalRead(row3)) button = 'C';
  if (teststate == digitalRead(row4)) button = 'D';
  waitForRelease(teststate); // Wait for release
  digitalWrite(col4, !teststate);

  return button; // Return the button pressed
}
void waitForRelease(bool state) {
  while (digitalRead(row1) == state) {
    delay(10); // Waits until pin is out of test state
  }
  while (digitalRead(row2) == state) {
    delay(10);
  }
  while (digitalRead(row3) == state) {
    delay(10);
  }
  while (digitalRead(row4) == state) {
    delay(10);
  }
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

void buttonAction() {
  buttonPressed = checkKeypad(); // Get key pressed, if any
  
  switch (buttonPressed) {
    case 'x':
      break; // Nothing was pressed
      
    // Changing fields
    case 'A':
      field--;
      lcd.clear();
      field = constrain(field, 0, numFields - 1);
      break;
    case 'B':
      field++;
      lcd.clear();
      field = constrain(field, 0, numFields - 1);
      break;

    // Next screen
    case 'C':
      screen++;
      lcd.clear();
      screen = constrain(screen, 0, numScreens - 1);
      field = 0;
      break;
    case 'D':
      screen--;
      lcd.clear();
      screen = constrain(screen, 0, numScreens - 1);
      field = 0;
      break;

    // Backspace
    case '#':
      if (fields[field + numFields * screen].length() > 0) {
        lcd.clear();
        fields[field + numFields * screen].remove(fields[field + numFields * screen].length() - 1); // Removes last character
      }
      break;

    // Adding digits and decimal places is done by concatenating the string
    default:
      if (buttonPressed == '*') {
        buttonPressed = '.'; // Decimal
      }
      // Only adds if not at full length
      if ( fields[field + numFields * screen].length() < maxFieldLength){
        fields[field + numFields * screen] += buttonPressed;
      }
      break;
  }
}

double currentTemp() {
  return readTemp(0); // Eventually will cycle through all probes and take average temp
}
double readTemp(const int index) {
  double temp, res;                // Used to store intermediate data and resistance of NTC
  const double beta = 3950.0;        // Beta for the thermistors
  
  // Find the resistance of the thermistor from voltage division (1023 is Vcc)
  res = ((1023.0 / analogRead(tempPin[index])) - 1);    // Finds ratio of set res to thermistor
  res *= setResis[index];
  //Serial.println(res);    // Print calculated resistance (used for debugging)
  
  // Finds temperature
  temp = (log(R25[index] / res));  // Take natural log of R25 over measured resistance 
  temp /= beta;                       // Divide by beta
  temp = T25[index] - temp;                 // Add 1/calibration temp, subtracted previous value
  temp = pow(temp, -1);               // Takes reciprical to get temperature in K
  temp -= 273.15;                      // Kelvin to Celsius

  if (temp < -50) temp = 0;
  
  return temp;
}

String oneDecimal(double input){
  input = round(input * 10);
  input /= 10;   // Rounds to 1 decimal place
  String output = String(input);    // Stores in temporary string

  int index = output.lastIndexOf(".");  // Find decimal
  if (index != -1) {
    if (output.length() - index > 2) {
      output.remove(index + 2, output.length() - (index + 2));    // Trims zeroes
    }
  }
  
  return output;
}
