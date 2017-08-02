#ifndef CHILLER_H
#define CHILLER_H

#include "Arduino.h"
#include "../temp/Thermistor.h"

class Chiller
{
  public:
    const char* name;
    Thermistor* thermistor;
    unsigned int controlPin;

    static int const memSpaceTotal = 128;
    int index;
    int addr;
    int setPointOffset = 0;
    int toleranceOffset = 1 * sizeof(float);
    int minCycleDurationOffset = 2 * sizeof(float);

    bool isOn;
    float setPoint;
    float tolerance;
    unsigned long previousCycleTime;
    unsigned int minCycleDuration_Minutes;

  public:
    Chiller( int index, unsigned int controlPin, Thermistor* thermistor, const char* name );
    virtual ~Chiller(){}
    void update();
    float readTemp();
    void cycle(bool on);

    void setSetPoint(float temp);
    void setTolerance(float tolerance);
    void setMinCycleDuration_Minutes(int minutes);
};

#endif
