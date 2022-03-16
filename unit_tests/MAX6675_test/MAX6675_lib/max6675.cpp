// this library is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"

/**************************************************************************/
/*!
    @brief  Initialize a MAX6675 sensor
    @param   SCLK The Arduino pin connected to Clock
    @param   CS The Arduino pin connected to Chip Select
    @param   MISO The Arduino pin connected to Data Out
*/
/**************************************************************************/
MAX6675::MAX6675(int8_t sclk, int8_t cs, int8_t so) {
  MAX_SO = so;
  MAX_SCK = sclk;
  MAX_CS = cs;
  
  pinMode(MAX_SCK, OUTPUT);
  pinMode(MAX_CS, OUTPUT);
  pinMode(MAX_SO, INPUT);

  digitalWrite(MAX_SCK, LOW);
  digitalWrite(MAX_CS, HIGH);
}

/**************************************************************************/
/*!
    @brief  Read the Celsius temperature
    @returns Temperature in C or NAN on failure!
*/
/**************************************************************************/
float MAX6675::getTemperature(void) {
  unsigned int temperature = 0;

  // Select chip
  digitalWrite(MAX_CS, LOW);

  // Collect data from MAX6675
  for (int i = 15; i >= 0; i--) {
    
    digitalWrite(MAX_SCK, LOW);
    delayMicroseconds(10);
    
    if (digitalRead(MAX_SO) == HIGH) {
      temperature |= (1 << i);
    }


    digitalWrite(MAX_SCK, HIGH);
    delayMicroseconds(10);
  }

  // Release chip
  digitalWrite(MAX_CS, HIGH);

  // Check if a thermocouple is attached
  if (temperature & 0x4) {
    return -1;
  }

  // Remove status bits from end
  temperature >>= 3;

  return float(temperature) * 0.25; // Return temperature in celsius
}
