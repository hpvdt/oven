#ifndef OVEN_TEMPERATURE_H
#define OVEN_TEMPERATURE_H

#include <Arduino.h>

// Functions related to using the MAX6675

void setupMAX6675(byte sclk, byte cs, byte so);

void setupTemperature();
float readTemperature();

#endif