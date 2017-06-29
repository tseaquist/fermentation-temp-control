#include "Chiller.h"
#include "EEPROM.h"
#include "Arduino.h"

Chiller::Chiller(int index)
{
  this->index = index;
  this->addr = index * memSpaceTotal;
  EEPROM.get(addr + setPointOffset, setPoint);
  EEPROM.get(addr + toleranceOffset, tolerance);
  EEPROM.get(addr + minCycleDurationOffset, minCycleDuration_Minutes);

  isOn = false;
  previousCycleTime = millis();
}

void Chiller::setSetPoint(float temp)
{
  this->setPoint = temp;
  EEPROM.put( addr + setPointOffset, temp );
}

void Chiller::setTolerance(float tolerance)
{
  this->tolerance = tolerance;
  EEPROM.put( addr + toleranceOffset, tolerance );
}

void Chiller::setMinCycleDuration_Minutes(int minutes)
{
  this->minCycleDuration_Minutes = minutes;
  EEPROM.put( addr + minCycleDurationOffset, minutes );
}

void Chiller::update()
{
  float temp = readTemp();
  bool aboveThreshold = temp > setPoint + tolerance;
  bool belowThreshold = temp < setPoint - tolerance;
  unsigned long sinceLastCycle = ( millis() - previousCycleTime );
  int sinceLastCycle_Minutes = ( int ) ( sinceLastCycle / 60000.0 );
  bool cycleSafe = sinceLastCycle_Minutes > minCycleDuration_Minutes;

  if(!isOn && aboveThreshold && cycleSafe)
  {
    cycle(true);
  }
  else if(isOn && belowThreshold)
  {
    cycle(false);
  }
}

void Chiller::cycle(bool on)
{
  isOn = on;
  if(!on)
  {
    previousCycleTime = millis();
  }
  //TODO implement turn-on turn-off relay
}

float Chiller::readTemp()
{
  //TODO read temperature from correct pin
  return 0;
}
