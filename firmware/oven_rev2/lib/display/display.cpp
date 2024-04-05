#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "display.hpp"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);

void setupDisplay() {
  // TODO: Figure out how to recover display control following WDT reset

  lcd.begin(20, 4);   // Set up display. 20 character in 4 rows
  lcd.clear();        // Clear the display

  // Splash screen
  printCenter(1, F("Oven Control System"));
  printCenter(2, F("Designed for HPDVT"));
  delay(1000);
  lcd.clear();
}

String oneDecimal(double input){
  input = round(input * 10);
  input /= 10;   // Rounds to 1 decimal place
  String output = String(input);    // Stores in temporary string

  int index = output.lastIndexOf(".");  // Find decimal
  if (index != -1) {
    if (output.length() - index > 2) {
      output.remove(index + 2, output.length() - (index + 2));    // Trims zeroes
    }
  }
  
  return output;
}

void printCenter(int row, String message) {
  int pos = 10 - (message.length() + 1) / 2; // Finds start to center message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printRight(int row, String message) {
  int pos = 20 - message.length(); // Finds start to right justify the message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printLeft(int row, String message) {
  lcd.setCursor(0, row);
  lcd.print(message);
}
void printCursor() {
  lcd.setCursor(19 - maxFieldLength, field);
  lcd.print('>');
}