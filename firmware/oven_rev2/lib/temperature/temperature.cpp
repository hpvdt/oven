#include <Arduino.h>

#include "temperature.hpp"

// Functions related to using the MAX6675

void setupMAX6675(byte sclk, byte cs, byte so) {

  pinMode(sclk, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(so, INPUT);

  digitalWrite(cs, HIGH);
}

float readTemperature(byte sclk, byte cs, byte so) {
  unsigned int temperature = 0;

  // Select chip
  digitalWrite(cs, LOW);

  // Collect data from MAX6675
  for (int i = 15; i >= 0; i--) {
    
    digitalWrite(sclk, LOW);
    delayMicroseconds(10);
    
    if (digitalRead(so) == HIGH) {
      temperature |= (1 << i);
    }


    digitalWrite(sclk, HIGH);
    delayMicroseconds(10);
  }

  // Release chip
  digitalWrite(cs, HIGH);

  // Check if a thermocouple is attached
  if (temperature & 0x4) {
    return -1;
  }

  // Remove status bits from end
  temperature >>= 3;

  return float(temperature) * 0.25; // Return temperature in celsius
}