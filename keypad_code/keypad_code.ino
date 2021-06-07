const int row1 = 2; // Row 1 pin
const int row2 = 3;
const int row3 = 4;
const int row4 = 5;
const int col1 = 6; // Column 1 pin
const int col2 = 7;
const int col3 = 8;
const int col4 = 9;
// Keypad works by detecting the intersection of a row and col pulling down an input. (A column pulling the row down)

const int heater = 10; // Heater relay pin

void setup() {
  pinMode(row1, INPUT_PULLUP); pinMode(row2, INPUT_PULLUP); pinMode(row3, INPUT_PULLUP); pinMode(row4, INPUT_PULLUP);
  pinMode(col1, OUTPUT);pinMode(col2, OUTPUT);pinMode(col3, OUTPUT);pinMode(col4, OUTPUT);

  pinMode(heater, OUTPUT); // Controls relay
  digitalWrite(heater, LOW); // Off by default

  Serial.begin(9600);
}

void loop() {
  delay(10);

  char buttonPressed;

  buttonPressed = checkKeypad();

  if (buttonPressed != 'x') {Serial.println(buttonPressed);}
}

// Checks keypad for what button is pressed (returns 'x' if nothing pressed)
char checkKeypad(){
  char button = 'x'; // Stores button pressed (x will return if nothing pressed)
  
  digitalWrite(col1, LOW);
  digitalWrite(col2, HIGH);
  digitalWrite(col3, HIGH);
  digitalWrite(col4, HIGH);

  if (not (digitalRead(row1))) button = '1';
  if (not (digitalRead(row2))) button = '4';
  if (not (digitalRead(row3))) button = '7';
  if (not (digitalRead(row4))) button = '*';
  waitForRelease(); // Wait for release
  digitalWrite(col1, HIGH);
  digitalWrite(col2, LOW);
  delay(1); // Delay to avoid transients

  if (not (digitalRead(row1))) button = '2';
  if (not (digitalRead(row2))) button = '5';
  if (not (digitalRead(row3))) button = '8';
  if (not (digitalRead(row4))) button = '0';
  waitForRelease(); // Wait for release
  digitalWrite(col2, HIGH);
  digitalWrite(col3, LOW);
  delay(1); // Delay to avoid transients

  if (not (digitalRead(row1))) button = '3';
  if (not (digitalRead(row2))) button = '6';
  if (not (digitalRead(row3))) button = '9';
  if (not (digitalRead(row4))) button = '#';
  waitForRelease(); // Wait for release
  digitalWrite(col3, HIGH);
  digitalWrite(col4, LOW);
  delay(1); // Delay to avoid transients

  if (not (digitalRead(row1))) button = 'A';
  if (not (digitalRead(row2))) button = 'B';
  if (not (digitalRead(row3))) button = 'C';
  if (not (digitalRead(row4))) button = 'D';
  waitForRelease(); // Wait for release
  digitalWrite(col4, HIGH);
  
  return button; // Return the button pressed
}
void waitForRelease(){
  while (digitalRead(row1) == LOW) {
    delay(10); // Waits until pin is HIGH
  } 
  while (digitalRead(row2) == LOW) {
    delay(10); // Waits until pin is HIGH
  } 
  while (digitalRead(row3) == LOW) {
    delay(10); // Waits until pin is HIGH
  } 
  while (digitalRead(row4) == LOW) {
    delay(10); // Waits until pin is HIGH
  } 
}
