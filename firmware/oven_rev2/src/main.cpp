#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "display.hpp"
#include "keypad.hpp"
#include "main.hpp"
#include "temperature.hpp"


// MAX6675 Pins
const byte MAX_SCK = A1;
const byte MAX_CS = 9;
const byte MAX_SO = A0;

// Heater 
const byte heater = 12;  // Heater relay pin
bool heaterState;       // State variable

// Control variables
int screen, field;                  // Used for display
const int numScreens = 4;           // Used as a limit for number of distinct screens
const int numFields = 3;            // Used as a limit for number of fields on a screen

// User input field configuration
const int maxFieldLength = 6;        // Max length of entered data
String fields[9];                    // Used to display entry data (should have numFields * numScreens elements)

int stage = 1;                          // Records cooking stage
double targetTemp, curTemp;              // Target and current temp
double temperature[5];                   // Used to store temp set points
const double tempTol = 5;                // Used as tolerance for over temp - IMPORTANT
unsigned long setPointTimes[5];         // Used for changes
double elapsedTime;                      // Used for status display
String endTime;                         // Used for status display (to minimize repeated instructions)

void setup() {
  setupDisplay();
  setupKeypad();

  pinMode(heater, OUTPUT);            // Controls relay
  heaterState = LOW;                  // Off by default
  digitalWrite(heater, heaterState);

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
      printRight(3, "Stg 2>");

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
      printRight(3, "Strt>");

      buttonAction(); // Performs button action

      // Check if starting oven
      if (screen == (numScreens - 2)) {
        stage = 1; // Entered first stage
        
        //Sets temperature points
        temperature[0] = readTemperature(MAX_SCK, MAX_CS, MAX_SO); // Record starting temp
        temperature[1] = fields[0].toFloat();
        temperature[2] = temperature[1];
        temperature[3] = fields[numFields].toFloat();
        temperature[4] = temperature[3];

        // Gets times
        // Times are (target - start) / ramp rate
        elapsedTime = 0;
        setPointTimes[0] = actualMillis();                                                          // Start time
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
      targetTemp = (actualMillis() - setPointTimes[stage - 1]) * (temperature[stage] - temperature[stage - 1]);
      targetTemp /= (setPointTimes[stage] - setPointTimes[stage - 1]);
      targetTemp += temperature[stage - 1];
      curTemp = readTemperature(MAX_SCK, MAX_CS, MAX_SO); // Gets current temp

      if (curTemp < targetTemp) {
        heaterState = HIGH;                   // Too cold
        digitalWrite(heater, heaterState);
      }
      else if (curTemp > (targetTemp + 1)) {
        heaterState = LOW;                    // Too hot
        digitalWrite(heater, heaterState);
      }
      
      // Time
      if (actualMillis() > setPointTimes[stage]) stage++; // Checks if approriate stage
      elapsedTime = actualMillis() - setPointTimes[0];    // Elaplsed time in ms
      elapsedTime /= 60000;                         // Elapsed time in minutes
      
      // Screen stuff
      printLeft(0, F("Cur/Tar"));
      printLeft(1, F("Elp/End"));
      printLeft(2, F("Heater"));
      printCenter(3, F("Oven Status"));

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
      printCenter(0, F("Process Complete"));
      printCenter(1, F("Oven is disabled"));
      printLeft(3, "Cur. Temp");
      printRight(3, "   " + oneDecimal(readTemperature(MAX_SCK, MAX_CS, MAX_SO)));

      // Turn off heater
      heaterState = LOW;                  
      digitalWrite(heater, heaterState);
      
      delay(1000);
      break;
  }

  delay(25);
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

// Function used to return a better approximation of time elasped
unsigned long actualMillis() {
  unsigned long trueMillis = millis();

  // millis() returns roughly 971 "milliseconds" per actual second due to the way millis() is set up with timers.
  // Scaling it up by a factor of 1.024 is needed to get roughly 1000 counts per actual second.
  // To keep it to integer math dividing by 125, multiplying by 128 is used.
  
  trueMillis = trueMillis / 125;
  trueMillis = trueMillis * 128;
  
  // Multiplication after division to avoid overflows with long work times
  
  return trueMillis;
}