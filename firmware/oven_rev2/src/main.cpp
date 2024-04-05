#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "display.hpp"
#include "keypad.hpp"
#include "main.hpp"
#include "temperature.hpp"
#include "watchdog.hpp"

// Heater 
const byte heater = PIN_PB0;          // Heater relay pin
bool heaterState;                     // Heater state

// Control variables
int screen, field;                    // Used for display state
const int numScreens = 4;             // Used as a limit for number of distinct screens
const int numFields = 3;              // Used as a limit for number of fields on a screen

// User input field configuration
const int maxFieldLength = 6;         // Max length of entered data
String fields[numFields][numScreens]; // Data fields on each screen

int bakeStage = 1;                    // Records baking stage
float temperature[5];                 // Stores temperature set points
const float tempTol = 3.0;            // Tolerance for under temperature - IMPORTANT!
unsigned long setPointTimes[5];       // Records time for changes
String endTime;                       // Used for status display (to minimize repeated calculation)

void setup() {
  disableWatchdog(); // Needs to go first to prevent repeated watchdog resets

  setupKeypad();
  setupTemperature();

  // Set heater to start off until programmed
  pinMode(heater, OUTPUT);
  heaterState = LOW;
  digitalWrite(heater, heaterState);

  setupDisplay();

  screen = 0;
  field = 0;

  enableWatchdog(); 
  // NOTE: Currently the screen will shutdown until a complete power cycle after WDT reset
}

void loop() {
  // Screen
  switch (screen) {
    case 0: // Setup first point
      printLeft(0, F("Target Temp"));
      printLeft(3, oneDecimal(readTemperature()) + "C "); // Show temp on initial screen for error check
      printLeft(1, F("Rise Rt. c/m"));
      printLeft(2, F("Hold Time (m)"));
      printCenter(3, F("Stg 1"));
      printCursor();
      for (int i = 0; i < numFields; i++) printRight(i, fields[i][screen]);
      printRight(3, "Stg 2>");

      heaterState = LOW;

      buttonAction(); // Performs button action
      break;
    case 1: // Second point config
      printLeft(0, F("Target Temp"));
      printLeft(1, F("Rise Rt. c/m"));
      printLeft(2, F("Hold Time (m)"));
      printLeft(3, F("<Stg 1"));
      printCenter(3, F("Stg 2"));
      printCursor();
      for (int i = 0; i < numFields; i++) printRight(i, fields[i][screen]);
      printRight(3, "Strt>");

      heaterState = LOW;

      buttonAction(); // Performs button action

      // Check if starting oven
      if (screen == (numScreens - 2)) {
        bakeStage = 1; // Entered first stage
        
        //Sets temperature points
        temperature[0] = readTemperature(); // Record starting temp
        temperature[1] = fields[0][0].toFloat();
        temperature[2] = temperature[1];
        temperature[3] = fields[0][1].toFloat();
        temperature[4] = temperature[3];

        // Gets times
        // Times are (target - start) / ramp rate
        setPointTimes[0] = actualMillis();                                                      // Start time
        setPointTimes[1] = (temperature[1] - temperature[0]) * 60000 / fields[1][0].toFloat();  // Uses rate and difference to find ramp time
        setPointTimes[2] = fields[2][0].toFloat() * 60000;                                      // Records hold time
        setPointTimes[3] = (temperature[3] - temperature[2]) * 60000 / fields[1][1].toFloat();  // Second ramp
        setPointTimes[4] = fields[2][1].toFloat() * 60000;                                      // Last hold

        for (int i = 1; i <= 4; i++) setPointTimes[i] += setPointTimes[i - 1]; // Makes the times cummulative
        endTime = int(ceil((setPointTimes[4] - setPointTimes[0]) / 60000)); // Records the end as a string for status display
      }
      break;
      
    case 2: // Runtime
      // Control
      // Gets linearly interpolated temperature based on time and bounding set points
      // map() outputs long int, needed floats so I adjusted their source code
      float targetTemp, curTemp;
      curTemp = readTemperature();
      targetTemp = (actualMillis() - setPointTimes[bakeStage - 1]) * (temperature[bakeStage] - temperature[bakeStage - 1]);
      targetTemp /= (setPointTimes[bakeStage] - setPointTimes[bakeStage - 1]);
      targetTemp += temperature[bakeStage - 1];

      if (curTemp < (targetTemp - tempTol)) heaterState = HIGH;
      else if (curTemp > targetTemp) heaterState = LOW;
      
      // Time
      float elapsedTime;
      elapsedTime = actualMillis() - setPointTimes[0];            // Elaplsed time in ms
      if (elapsedTime > setPointTimes[bakeStage]) bakeStage++;    // Checks if approriate stage
      elapsedTime /= 60000;                                       // Elapsed time in minutes
      
      // Screen stuff
      printLeft(1, F("Cur/Tar"));
      printLeft(2, F("Elp/End"));
      printLeft(3, F("Heater"));
      printCenter(0, F("Oven Status"));

      // Fields
      fields[0][screen] = "  ";
      fields[0][screen] += oneDecimal(curTemp);
      fields[0][screen] += "/";
      fields[0][screen] += oneDecimal(targetTemp);

      fields[1][screen] = oneDecimal(elapsedTime);
      fields[1][screen] += "/";
      fields[1][screen] += endTime;

      if (heaterState) fields[2][screen] = " ON";
      else fields[2][screen] = "OFF";

      for (int i = 0; i < numFields; i++) printRight(i + 1, fields[i][screen]);

      // Check and handle reset condition
      if (checkKeypad() == 'E') {
        screen = 0;
        field = 0;
        heaterState = LOW;
      }

      // Check for finish (past stage 4)
      if (bakeStage > 4) {
        screen++;
        lcd.clear();
      }
      delay(300); // Extending cycle time during run time
      break;
      
    case 3: // Finished
      printCenter(0, F("Process Complete"));
      printCenter(1, F("Oven is disabled"));
      printLeft(3, "Cur. Temp");
      printRight(3, "   " + oneDecimal(readTemperature()));

      heaterState = LOW; // Turn off heater for safety
      
      delay(200); // Slow down code in cooldown period
      break;
  }

  digitalWrite(heater, heaterState);
  delay(25);

  resetWatchdog();
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

    // Changing screen
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
      if (fields[field][screen].length() > 0) {
        lcd.clear(); // Need to clear screen to remove leading character
        fields[field][screen].remove(fields[field][screen].length() - 1); // Removes last character
      }
      break;

    // Adding digits and decimal places is done by concatenating the string
    default:
      if (buttonPressed == '*') buttonPressed = '.'; // Decimal conversion

      // Only adds if not at full length
      if (fields[field][screen].length() < maxFieldLength) fields[field][screen] += buttonPressed;
      break;
  }
}

/**
 * @brief A more accurate time
 * 
 * @note Takes the value from `millis()` and adjusts it to counter resonator and implementation inaccuracies
 * 
 * @return Adjusted millisecond count 
 */
unsigned long actualMillis() {
  unsigned long trueMillis = millis();

  // millis() returns roughly 971 "milliseconds" per actual second due to the way millis() is set up with timers.
  // Scaling it up by a factor of 1.024 is needed to get roughly 1000 counts per actual second.
  // To keep it to integer math dividing by 125, multiplying by 128 is used.
  
  trueMillis = trueMillis / 125;
  trueMillis = trueMillis * 128;
  
  // Multiplication after division to avoid overflows with long work times

  // This is scaling based on board specific resonator tolerance
  trueMillis = trueMillis / 1000;
  trueMillis = trueMillis *  977;
  
  return trueMillis;
}