
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
