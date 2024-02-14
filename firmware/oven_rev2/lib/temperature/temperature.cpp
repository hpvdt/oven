#include <Arduino.h>

#ifdef USE_MAX6675
    #include "max6675.hpp"
#endif

#ifdef USE_MAX31855
    #include <Adafruit_MAX31855.h>

    const byte MAXDO     = A0;
    const byte MAXCS     = 9;
    const byte MAXCLK    = A1;

    Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
#endif

#include "temperature.hpp"

void setupTemperature() {

#ifdef USE_MAX6675
    setupMAX6675();
#endif

#ifdef USE_MAX31855
    thermocouple.begin();
#endif
}

float readTemperature() {

#ifdef USE_MAX6675
    return readTemperatureMAX6675();
#endif

#ifdef USE_MAX31855
    float reading = thermocouple.readCelsius();
    if (isnan(reading)) return -1;
    else return reading;
#endif
}