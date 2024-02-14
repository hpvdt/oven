#ifndef MAX6675_H
#define MAX6675_H

#include "Arduino.h"

class MAX6675 {
public:
  MAX6675(int8_t sclk, int8_t cs, int8_t so);

  float readTemperature(void);

private:
  int8_t MAX_SCK, MAX_SO, MAX_SC;
};

#endif
