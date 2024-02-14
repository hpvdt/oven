#ifndef OVEN_KEYPAD_H
#define OVEN_KEYPAD_H

#include <Arduino.h>

extern char buttonPressed;

// Checks keypad for what button is pressed (returns 'x' if nothing pressed)
void setupKeypad();
char checkKeypad();
void waitForRelease(bool state);

#endif