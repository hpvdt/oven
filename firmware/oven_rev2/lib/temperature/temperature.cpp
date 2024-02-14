#include <Arduino.h>

#include "max6675.hpp"
#include "temperature.hpp"

void setupTemperature() {
    setupMAX6675();
}

float readTemperature() {
  return readTemperatureMAX6675();
}