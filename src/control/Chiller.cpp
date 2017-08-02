#include "Chiller.h"
#include <EEPROM.h>

Chiller::Chiller(int index, unsigned int controlPin, Thermistor* thermistor, const char* name)
{
  this->controlPin = controlPin;
  this->thermistor = thermistor;
  this->name = name;
  this->index = index;
  this->addr = index * memSpaceTotal;
  EEPROM.get(addr + setPointOffset, setPoint);
  EEPROM.get(addr + toleranceOffset, tolerance);
  EEPROM.get(addr + minCycleDurationOffset, minCycleDuration_Minutes);

  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW);

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
  unsigned int sinceLastCycle_Minutes = ( unsigned ) ( sinceLastCycle / 60000.0 );
  bool cycleSafe = sinceLastCycle_Minutes >= minCycleDuration_Minutes;

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
  if(isOn == on) return;
  isOn = on;
  if(!on)
  {
    previousCycleTime = millis();
  }
  digitalWrite(controlPin, on ? HIGH : LOW);
}

float Chiller::readTemp()
{
  return thermistor->getTemp();
}
