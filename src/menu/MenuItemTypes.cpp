#include "MenuItemTypes.h"

SetPoint::SetPoint(Chiller* chiller) : MenuItem("Set Point")
{
  this->chiller = chiller;
  selection = chiller->setPoint;
  setValue(toString(selection));
}
MenuItem* SetPoint::turn(int count)
{
  selection += count / 10.0;
  selection = shorten(selection);
  if(selection != chiller->setPoint)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* SetPoint::click()
{
  chiller->setSetPoint(selection);
  const char* str = toString(selection);
  setValue(str);
  up->setContainerValue(str);
  return up;
}
MenuItem* SetPoint::back()
{
  reset();
  return MenuItem::back();
}
void SetPoint::reset()
{
  selection = chiller->setPoint;
  setValue(String(selection, 1).c_str());
}

////////////TOLERANCE

Tolerance::Tolerance(Chiller* chiller) : MenuItem("Tolerance")
{
  this->chiller = chiller;
  selection = chiller->tolerance;
  setValue(toString(selection));
}
MenuItem* Tolerance::turn(int count)
{
  selection += count / 10.0;
  selection = shorten(selection);
  if(selection != chiller->tolerance)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* Tolerance::click()
{
  chiller->setTolerance(selection);
  const char* str = toString(selection);
  setValue(str);
  up->setContainerValue(str);
  return up;
}
MenuItem* Tolerance::back()
{
  reset();
  return MenuItem::back();
}
void Tolerance::reset()
{
  selection = chiller->tolerance;
  setValue(toString(selection));
}

//////////CYCLE DURATION

CycleDuration::CycleDuration(Chiller* chiller) : MenuItem("Cycle Guard Mins")
{
  this->chiller = chiller;
  selection = chiller->minCycleDuration_Minutes;
  setValue(toString(selection));
}
MenuItem* CycleDuration::turn(int count)
{
  selection += count;
  if(selection != chiller->minCycleDuration_Minutes)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* CycleDuration::click()
{
  chiller->setMinCycleDuration_Minutes(selection);
  setValue(toString(selection));
  up->setContainerValue(value);
  return up;
}
MenuItem* CycleDuration::back()
{
  reset();
  return MenuItem::back();
}
void CycleDuration::reset()
{
  selection = chiller->minCycleDuration_Minutes;
  setValue(toString(selection));
}

////////////RAMP MODE

RampMode::RampMode(FermentChiller* chiller) : MenuItem("Ramp Mode")
{
  this->chiller = chiller;
  selection = chiller->rampModeOn;
  setValue(toString(selection));
}
MenuItem* RampMode::turn(int count)
{
  if(count != 0)
  {
    selection = !selection;
  }
  if(selection != chiller->rampModeOn)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* RampMode::click()
{
  const char* str = toString(selection);
  setValue(str);
  up->setContainerValue(str);
  if(selection)
  {
    if(selection == chiller->rampModeOn)
    {
      return down;
    }
    float currentTemp = chiller->readTemp();
    chiller->setRampModeOn(selection);
    chiller->setSetPoint(currentTemp);
    chiller->setRampStartTemp(currentTemp);
    chiller->setRampEndTemp(currentTemp + 5.0);
    chiller->setRampCurrentDuration_Hours(0);
    chiller->setRampTotalDuration_Hours(48);
    down->reset();
    return down;
  }
  else
  {
    return up;
  }
}
MenuItem* RampMode::back()
{
  reset();
  return MenuItem::back();
}
void RampMode::reset()
{
  selection = chiller->rampModeOn;
  setValue(toString(selection));
}

////////////RAMP DURATION

RampDuration::RampDuration(FermentChiller* chiller) : MenuItem("Ramp Length Hrs")
{
  this->chiller = chiller;
  selection = chiller->rampTotalDuration_Hours;
  setValue(toString(selection));
}
MenuItem* RampDuration::turn(int count)
{
  selection += count;
  if(selection != chiller->rampTotalDuration_Hours)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* RampDuration::click()
{
  chiller->setRampTotalDuration_Hours(selection);
  chiller->setRampCurrentDuration_Hours(0);
  chiller->previousCycleTime = millis();
  setValue(toString(selection));
  down->reset();
  return down;
}
MenuItem* RampDuration::back()
{
  reset();
  return MenuItem::back();
}
void RampDuration::reset()
{
  selection = chiller->rampTotalDuration_Hours;
  setValue(toString(selection));
}

////////////RAMP START TEMP

RampStartTemp::RampStartTemp(FermentChiller* chiller) : MenuItem("Start Temp")
{
  this->chiller = chiller;
  selection = chiller->rampStartTemp;
  setValue(toString(selection));
}
MenuItem* RampStartTemp::turn(int count)
{
  selection += count / 10.0;
  selection = shorten(selection);
  if(selection != chiller->rampStartTemp)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* RampStartTemp::click()
{
  chiller->setRampStartTemp(selection);
  setValue(toString(selection));
  down->reset();
  return down;
}
MenuItem* RampStartTemp::back()
{
  reset();
  return MenuItem::back();
}
void RampStartTemp::reset()
{
  selection = chiller->rampStartTemp;
  setValue(toString(selection));
}

////////////RAMP END TEMP

RampEndTemp::RampEndTemp(FermentChiller* chiller) : MenuItem("End Temp")
{
  this->chiller = chiller;
  selection = chiller->rampEndTemp;
  setValue(toString(selection));
}
MenuItem* RampEndTemp::turn(int count)
{
  selection += count / 10.0;
  selection = shorten(selection);
  if(selection != chiller->rampEndTemp)
  {
    setValueOption(toString(selection));
  }
  else
  {
    setValue(toString(selection));
  }
  return this;
}
MenuItem* RampEndTemp::click()
{
  chiller->setRampEndTemp(selection);
  setValue(toString(selection));
  return up->up->up->up;
}
MenuItem* RampEndTemp::back()
{
  reset();
  return MenuItem::back();
}
void RampEndTemp::reset()
{
  selection = chiller->rampEndTemp;
  setValue(toString(selection));
}
