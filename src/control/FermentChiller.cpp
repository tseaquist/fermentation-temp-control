#include "FermentChiller.h"
#include <EEPROM.h>

FermentChiller::FermentChiller(int index, unsigned int controlPin, Thermistor* thermistor, const char* name)
: Chiller(index, controlPin, thermistor, name)
{
  EEPROM.get(addr + rampModeOnOffset, rampModeOn);
  if(rampModeOn)
  {
    EEPROM.get(addr + rampStartTempOffset, rampStartTemp);
    EEPROM.get(addr + rampEndTempOffset, rampEndTemp);
    EEPROM.get(addr + rampCurrentDurationOffset, rampCurrentDuration_Hours);
    EEPROM.get(addr + rampTotalDurationOffset, rampTotalDuration_Hours);

    rampStartTemp = getRampSetPoint(rampCurrentDuration_Hours);
    rampTotalDuration_Hours -= rampCurrentDuration_Hours;
    rampCurrentDuration_Hours = 0;
    rampStartTime = millis();
  }
}

void FermentChiller::update()
{
  if(rampModeOn)
  {
    unsigned long sinceStart = ( millis() - rampStartTime );
    unsigned int nextDuration_Hours = ( int ) ( sinceStart / 3600000.0 );
    if(nextDuration_Hours > rampCurrentDuration_Hours)
    {
      setRampCurrentDuration_Hours(nextDuration_Hours);
      float nextSetPoint = getRampSetPoint(rampCurrentDuration_Hours);
      setSetPoint(nextSetPoint);
    }
  }
  Chiller::update();
}

float FermentChiller::getRampSetPoint(unsigned int rampCurrentDuration_Hours)
{
  if(rampCurrentDuration_Hours > rampTotalDuration_Hours)
  {
    setRampModeOn(false);
    setSetPoint(rampEndTemp);
    return rampEndTemp;
  }
  else
  {
    return rampStartTemp + (rampEndTemp - rampStartTemp)
    * (float) rampCurrentDuration_Hours / (float)rampTotalDuration_Hours;
  }
}

void FermentChiller::setRampModeOn(bool on)
{
  this->rampModeOn = on;
  EEPROM.put(addr + rampModeOnOffset, on);
}
void FermentChiller::setRampStartTemp(float temp)
{
  this->rampStartTemp = temp;
  EEPROM.put(addr + rampStartTempOffset, temp);
}
void FermentChiller::setRampEndTemp(float temp)
{
  this->rampEndTemp = temp;
  EEPROM.put(addr + rampEndTempOffset, temp);
}
void FermentChiller::setRampCurrentDuration_Hours(unsigned int hours)
{
  this->rampCurrentDuration_Hours = hours;
  EEPROM.put(addr + rampCurrentDurationOffset, hours);
}
void FermentChiller::setRampTotalDuration_Hours(unsigned int hours)
{
  this->rampTotalDuration_Hours = hours;
  EEPROM.put(addr + rampTotalDurationOffset, hours);
}
