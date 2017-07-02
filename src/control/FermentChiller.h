#ifndef FERMENT_H
#define FERMENT_H

#include "Chiller.h"
#include "Arduino.h"
#include "../util/stringutil.h"

class FermentChiller : public Chiller
{
  public:
    bool rampModeOn;
    float rampStartTemp;
    float rampEndTemp;
    unsigned int rampCurrentDuration_Hours;
    unsigned int rampTotalDuration_Hours;
    unsigned long rampStartTime;

    int rampModeOnOffset = 2 * sizeof(float) + 1 * sizeof(int);
    int rampStartTempOffset = 2 * sizeof(float) + 1 * sizeof(int)
      + 1 * sizeof(bool);
    int rampEndTempOffset = 2 * sizeof(float) + 2 * sizeof(int)
      + 1 * sizeof(bool);
    int rampCurrentDurationOffset = 2 * sizeof(float) + 3 * sizeof(int)
      + 1 * sizeof(bool);
    int rampTotalDurationOffset = 2 * sizeof(float) + 4 * sizeof(int)
      + 1 * sizeof(bool);

  public:
    FermentChiller( int index, const char* name );
    void update();
    float getRampSetPoint(unsigned int rampTotalDuration_Hours);

    void setRampModeOn(bool on);
    void setRampStartTemp(float temp);
    void setRampEndTemp(float temp);
    void setRampCurrentDuration_Hours(unsigned int hours);
    void setRampTotalDuration_Hours(unsigned int hours);
};

#endif
