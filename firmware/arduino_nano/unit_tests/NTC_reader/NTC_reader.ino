#include <math.h>

const int tempPin[] = {14};
const double setResis[] = {10000.0}; // Stores set resistor values
const double R25[] = {100000.0}; // Stores the calibration value of each NTC
const double T25[] = {0.0033557047}; // Stores the reciprical (^-1) of the calibration temperature in K

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // Cyclically prints recorded temperature
  
  delay(500);
  Serial.println(readTemp(0));
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

  return temp;
}
