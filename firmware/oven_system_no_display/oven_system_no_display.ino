#include <math.h>
/* Information:
 *  
 * Pretty basic, enter data for each step in the configuration section 
 * following this. If you only have a single step process, fill the
 * values for step two with identical values for stage one but with a 
 * short (0.1 minute) hold time.
 * 
 * With the values input, upload to the arduino NANO, make sure to set
 * the "PROCESSOR" (under "Tools" menu) to "ATmega328P (Old Bootloader)".
 * 
 * If no errors are encountered the built in LED on the Arduino (labelled
 * "L") will be alight for the duration of the oven cycle. It will turn
 * off at the end of the cycle 
 */

 
////////////////////////////////////////////////
// CONFIGURATION
float temperature1 = 100;   // Deg C
float temperature2 = 105;
float rate1 = 5;          // C per minute
float rate2 = 2;
long hold1 = 10;             // Time to hold each temp in minutes
long hold2 = 3;

////////////////////////////////////////////////









const int heater = 2;  // Heater relay pin
bool heaterState;       // State variable

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
  Serial.begin(9600);
  
  pinMode(heater, OUTPUT);            // Controls relay
  heaterState = LOW;                  // Off by default
  digitalWrite(heater, heaterState);

  /////////////////////////////////////////
  // Point setup
  stage = 1; // Entered first stage
  
  //Sets temperature points
  temperature[0] = currentTemp(); // Record starting temp
  temperature[1] = temperature1;
  temperature[2] = temperature[1];
  temperature[3] = temperature2;
  temperature[4] = temperature[3];

  // Gets times
  // Times are (target - start) / ramp rate
  elapsedTime = 0;
  setPointTimes[0] = millis();                                            // Start time
  setPointTimes[1] = (temperature[1] - temperature[0]) * 60000 / rate1;   // Uses rate and difference to find ramp time
  setPointTimes[2] = hold1 * 60000;                                       // Records hold time
  setPointTimes[3] = (temperature[3] - temperature[2]) * 60000 / rate2;   // Second ramp
  setPointTimes[4] = hold2 * 60000;                                       // Last hold

  for (int i = 1; i <= 4; i++) {
    setPointTimes[i] += setPointTimes[i - 1]; //Makes the times cummulative
  }
  endTime = int(ceil((setPointTimes[4] - setPointTimes[0]) / 60000)); // Records the end as a string for status display

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // Outputs that the system is running
}

void loop() {
  if (stage < 5) {
  // Control
  // Gets linearly interpolated temperature based on time and bounding set points
  // map() outputs long int, needed floats so I adjusted their source code
  targetTemp = (millis() - setPointTimes[stage - 1]) * (temperature[stage] - temperature[stage - 1]);
  targetTemp /= (setPointTimes[stage] - setPointTimes[stage - 1]);
  targetTemp += temperature[stage - 1];
  curTemp = currentTemp(); // Gets current temp
  
  Serial.println(curTemp); // Prints temperature

  
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
  }

  // If the oven is done
  if (stage == 5) {
    Serial.println("DONE");
    // Turn off heater
    heaterState = LOW;                  
    digitalWrite(heater, heaterState);
    digitalWrite(13, LOW);                // Outputs that the system is off
    delay(10000);                         // Kill time
  }
  delay(300); // Extending cycle time during run time
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
