
double currentTemp() {
  // Calculates average of all temps
  
  float temperature = 0.0;
  
  if (numProbes > 0) { // Only does this if there are probes connected
    for (int i = 0; i<numPorts; i++){
      temperature += readTemp(i); // Sums all temperatures
      //Serial.println(temperature);
    }
    temperature /= numProbes; // Gets average
  }
  return temperature; // Eventually will cycle through all probes and take average temp
}
double readTemp(const int index) {
  if (!connectedProbes[index]) return 0; // Returns a zero if disconnected
  
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

  //Serial.println(temp);
  if (temp < -50) temp = 0;
  
  return temp;
}
