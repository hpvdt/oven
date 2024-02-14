#include <Arduino.h>

#include "keypad.hpp"

// Keypad config
const byte row1 = 3; // Row 1 pin
const byte row2 = 2;
const byte row3 = A3;
const byte row4 = A2;
const byte col1 = 7; // Column 1 pin
const byte col2 = 6;
const byte col3 = 5;
const byte col4 = 4;

char buttonPressed;
// Keypad works by detecting the intersection of a row and col pulling down an input. (A column pulling the row down)

void setupKeypad() {
    pinMode(row1, INPUT_PULLUP); 
    pinMode(row2, INPUT_PULLUP);
    pinMode(row3, INPUT_PULLUP);
    pinMode(row4, INPUT_PULLUP);
    pinMode(col1, OUTPUT);
    pinMode(col2, OUTPUT);
    pinMode(col3, OUTPUT);
    pinMode(col4, OUTPUT);
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