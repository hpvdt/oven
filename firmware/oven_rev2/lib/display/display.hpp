#ifndef OVEN_DISPLAY_H
#define OVEN_DISPLAY_H

#include <Arduino.h>

extern LiquidCrystal_I2C lcd;
extern const int maxFieldLength;
extern int field;

void setupDisplay();

String oneDecimal(double input);
void printCenter(int row, String message);
void printRight(int row, String message);
void printLeft(int row, String message);
void printCursor();

#endif