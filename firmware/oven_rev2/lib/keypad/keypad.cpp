#include <Arduino.h>

#include "keypad.hpp"

// Keypad config
const byte row1 = PIN_PD3;
const byte row2 = PIN_PD2;
const byte row3 = PIN_PC3;
const byte row4 = PIN_PC2;
const byte col1 = PIN_PD7;
const byte col2 = PIN_PD6;
const byte col3 = PIN_PD5;
const byte col4 = PIN_PD4;

char buttonPressed;
// Keypad works by detecting the intersection of a row and col pulling down an input. (A column pulling the row down)

void waitForRelease(bool holdstate); // Keep it locally scoped

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

/**
 * @brief Checks keypad for what button is pressed
 * 
 * @return char for button pressed (e.g. '`2`'). '`x`' if nothing is pressed.
 */
char checkKeypad() {
    const bool teststate = LOW; // Are we looking for highs or lows?

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
    delayMicroseconds(1000); // Delay to avoid transients

    if (teststate == digitalRead(row1)) button = '2';
    if (teststate == digitalRead(row2)) button = '5';
    if (teststate == digitalRead(row3)) button = '8';
    if (teststate == digitalRead(row4)) button = '0';
    waitForRelease(teststate);
    digitalWrite(col2, !teststate);
    digitalWrite(col3, teststate);
    delayMicroseconds(1000);

    if (teststate == digitalRead(row1)) button = '3';
    if (teststate == digitalRead(row2)) button = '6';
    if (teststate == digitalRead(row3)) button = '9';
    if (teststate == digitalRead(row4)) button = '#';
    waitForRelease(teststate);
    digitalWrite(col3, !teststate);
    digitalWrite(col4, teststate);
    delayMicroseconds(1000);

    if (teststate == digitalRead(row1)) button = 'A';
    if (teststate == digitalRead(row2)) button = 'B';
    if (teststate == digitalRead(row3)) button = 'C';
    if (teststate == digitalRead(row4)) button = 'D';
    waitForRelease(teststate);
    digitalWrite(col4, !teststate);

    return button;
}

/**
 * @brief Blocks program if a pin is in a given state
 * 
 * @param holdstate the state to hold if encountered on a pin
 */
void waitForRelease(bool holdstate) {
    // Waits until pins are out of test state
    while (digitalRead(row1) == holdstate) delay(5);
    while (digitalRead(row2) == holdstate) delay(5);
    while (digitalRead(row3) == holdstate) delay(5);
    while (digitalRead(row4) == holdstate) delay(5);
}