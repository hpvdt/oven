#include <Arduino.h>

#include "max6675.hpp"

// MAX6675 Pins
const byte MAX_SCK  = PIN_PC1;
const byte MAX_CS   = PIN_PB1;
const byte MAX_SO   = PIN_PC0;

void setupMAX6675() {
    pinMode(MAX_SCK, OUTPUT);
    pinMode(MAX_CS, OUTPUT);
    pinMode(MAX_SO, INPUT);

    digitalWrite(MAX_CS, HIGH);
}

/**
 * @brief Reads temperature from MAX6675 chip
 * @note Uses bit-banged SPI so not the fastest implementation. Consider switching to a library.
 * 
 * @return Temperature in Celsius as float. -1 if there is an error.
 */
float readTemperatureMAX6675() {
    uint16_t temperature = 0;

    digitalWrite(MAX_CS, LOW); // Select chip

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

    digitalWrite(MAX_CS, HIGH); // Release chip

    // Check if a thermocouple is attached
    if (temperature & 0x6) return -2.2;
    
    // Remove status bits from end
    temperature >>= 3;

    return float(temperature) * 0.25; // Return temperature in celsius
}