#ifndef TEMP_H
#define TEMP_H

#include "Arduino.h"
#include <math.h>

class Thermistor
{
  protected:
    unsigned int pin;
    double resistor;
    double steinhartA1; //First Steinhart-Hart coefficient.
    double steinhartA2; //Second Steinhart-Hart coefficient.
    double steinhartA3; //Third Steinhart-Hart coefficient.
    double steinhartA4; //Fourth Steinhart-Hart coefficient.
    unsigned long lastUpdate;
    float lastTemp;
    unsigned int bitResolution = 1023;
    float voltage = 3.3;

  public:
    Thermistor(unsigned int pin, double resistor, double A1, double A2, double A3, double A4);
    void update();
    float getTemp();
    double getResistance();
};
#endif
