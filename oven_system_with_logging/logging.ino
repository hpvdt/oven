void logData() {
  File logfile = SD.open(filename, FILE_WRITE); // Opens file

  // Prepares data string
  String data = "";
  data = String(elapsedTime, 1) + ",";
  data += String(targetTemp, 1) + ",";
  data += String(curTemp, 1) + ",";
  data += String(heaterState) + ",";
  for (int i = 0; i < (numPorts); i++) {
    data += String(readTemp(i), 1) + ",";
  }

  logfile.println(data);
  logfile.close();
}

void recordConfig() {
  File logfile = SD.open(filename, FILE_WRITE);   // Opens file for writing config
  if (logfile) {
    logfile.println(F("Target Temp 1,Rise Rate 1 c/min,Hold Time 1 (min),Target Temp 2, Rise Rate 2 c/min, Hold Time 2 (min)"));
    for (int i = 0; i < 5; i++){
      logfile.print(fields[i] + ",");
    }
    logfile.println(fields[5]); // Ends line
    logfile.println(F("Elapsed time (min),Target Temp,Measured Temp,Heater Status,Probe 1,Probe 2,Probe 3"));  // Header
  }
  logfile.close();  // Closes file
}
