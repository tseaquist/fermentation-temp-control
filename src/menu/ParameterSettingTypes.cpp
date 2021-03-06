#include "ParameterSettingTypes.h"

const char* newSelect = "?";
const char* notActive = "~";
const char* on = "ON";
const char* off = "OFF";

FloatItem::FloatItem(Chiller* chiller):MenuItem()
{
  this->chiller = chiller;
  active = false;
}
MenuItem* FloatItem::turn(int count)
{
  if(!active)
  {
    return MenuItem::turn(count);
  }
  selection += count / 10.0;
  selection = shorten(selection);
  return this;
}

IntItem::IntItem(Chiller* chiller):MenuItem()
{
  this->chiller = chiller;
  active = false;
}
MenuItem* IntItem::turn(int count)
{
  if(!active)
  {
    return MenuItem::turn(count);
  }
  int val = selection;
  val += count;
  selection = val < 0 ? 0 : val;
  return this;
}

BoolItem::BoolItem(Chiller* chiller):MenuItem()
{
  this->chiller = chiller;
  active = false;
}
MenuItem* BoolItem::turn(int count)
{
  if(!active)
  {
    return MenuItem::turn(count);
  }
  if(count != 0)
  {
    selection = !selection;
  }
  return this;
}

SetPoint::SetPoint(Chiller* chiller) : FloatItem(chiller)
{
  selection = chiller->setPoint;
}
void SetPoint::getTitle(char* title)
{
  strncpy(title, "Set Point", 16);
}
void SetPoint::getValue(char* value)
{
  if(!active)
  {
    int offset = 0;
    strncpy(value, notActive, 16);
    offset = strlen(value);
    dtostrf((double)selection, 0, 1, value + offset);
    return;
  }
  if(selection == chiller->setPoint)
  {
    dtostrf((double)selection, 0, 1, value);
  }
  else
  {
    dtostrf((double)selection, 0, 1, value);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* SetPoint::click()
{
  if(!active)
  {
    active = true;
    return this;
  }
  active = false;
  chiller->setSetPoint(selection);
  return back();
}
MenuItem* SetPoint::back()
{
  reset();
  if(active)
  {
    active = false;
    return this;
  }
  return MenuItem::back();
}
void SetPoint::reset()
{
  selection = chiller->setPoint;
}

Tolerance::Tolerance(Chiller* chiller) : FloatItem(chiller)
{
  selection = chiller->tolerance;
}
void Tolerance::getTitle(char* title)
{
  strncpy(title, "Tolerance", 16);
}
void Tolerance::getValue(char* value)
{
  if(!active)
  {
    int offset = 0;
    strncpy(value, notActive, 16);
    offset = strlen(value);
    dtostrf((double)selection, 0, 1, value + offset);
    return;
  }
  if(selection == chiller->tolerance)
  {
    dtostrf((double)selection, 0, 1, value);
  }
  else
  {
    dtostrf((double)selection, 0, 1, value);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* Tolerance::click()
{
  if(!active)
  {
    active = true;
    return this;
  }
  active = false;
  chiller->setTolerance(selection);
  return back();
}
MenuItem* Tolerance::back()
{
  reset();
  if(active)
  {
    active = false;
    return this;
  }
  return MenuItem::back();
}
void Tolerance::reset()
{
  selection = chiller->tolerance;
}

CycleDuration::CycleDuration(Chiller* chiller) : IntItem(chiller)
{
  selection = chiller->minCycleDuration_Minutes;
}
void CycleDuration::getTitle(char* title)
{
  strncpy(title, "Min Cycle Mins", 16);
}
void CycleDuration::getValue(char* value)
{
  if(!active)
  {
    int offset = 0;
    strncpy(value, notActive, 16);
    offset = strlen(value);
    utoa(selection, value + offset, 10);
    return;
  }
  if(selection == chiller->minCycleDuration_Minutes)
  {
    utoa(selection, value, 10);
  }
  else
  {
    utoa(selection, value, 10);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* CycleDuration::click()
{
  if(!active)
  {
    active = true;
    return this;
  }
  active = false;
  chiller->setMinCycleDuration_Minutes(selection);
  return back();
}
MenuItem* CycleDuration::back()
{
  reset();
  if(active)
  {
    active = false;
    return this;
  }
  return MenuItem::back();
}
void CycleDuration::reset()
{
  selection = chiller->minCycleDuration_Minutes;
}

RampMode::RampMode(FermentChiller* chiller) : BoolItem(chiller)
{
  this->fermentChiller = chiller;
  selection = fermentChiller->rampModeOn;
}
void RampMode::getTitle(char* title)
{
  strncpy(title, "Ramp Mode", 16);
}
void RampMode::getValue(char* value)
{
  if(!active)
  {
    int offset = 0;
    strncpy(value, notActive, 16);
    offset = strlen(value);
    strncpy(value + offset, selection ? on : off, 16 - offset);
    return;
  }
  if(selection == fermentChiller->rampModeOn)
  {
    strncpy(value, selection ? on : off, 16);
  }
  else
  {
    strncpy(value, selection ? on : off, 16);
    strncat(value, newSelect, 16 - strlen(value));
  }
}
MenuItem* RampMode::click()
{
  if(!active)
  {
    active = true;
    return this;
  }
  if(selection)
  {
    if(selection == fermentChiller->rampModeOn)
    {
      return down;
    }
    float currentTemp = chiller->readTemp();
    currentTemp = currentTemp > 32 ? currentTemp : 32;
    fermentChiller->rampStartTime = millis();
    fermentChiller->setRampCurrentDuration_Hours(0);
    fermentChiller->setRampTotalDuration_Hours(48);
    fermentChiller->setRampModeOn(selection);
    fermentChiller->setSetPoint(currentTemp);
    fermentChiller->setRampStartTemp(currentTemp);
    fermentChiller->setRampEndTemp(currentTemp + 5.0);
    down->reset();
    return down;
  }
  else
  {
    fermentChiller->setRampModeOn(selection);
    active = false;
    return back();
  }
}
MenuItem* RampMode::back()
{
  reset();
  if(active)
  {
    active = false;
    return this;
  }
  return MenuItem::back();
}
void RampMode::reset()
{
  selection = fermentChiller->rampModeOn;
}

RampDuration::RampDuration(FermentChiller* chiller) : IntItem(chiller)
{
  this->fermentChiller = chiller;
  selection = fermentChiller->rampTotalDuration_Hours;
  active = true;
}
void RampDuration::getTitle(char* title)
{
  strncpy(title, "Ramp Length Hrs", 16);
}
void RampDuration::getValue(char* value)
{
  if(selection == fermentChiller->rampTotalDuration_Hours)
  {
    utoa(selection, value, 10);
  }
  else
  {
    utoa(selection, value, 10);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* RampDuration::click()
{
  fermentChiller->rampStartTime = millis();
  fermentChiller->setRampCurrentDuration_Hours(0);
  fermentChiller->setRampTotalDuration_Hours(selection);
  fermentChiller->previousCycleTime = millis();
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
  selection = fermentChiller->rampTotalDuration_Hours;
}

RampStartTemp::RampStartTemp(FermentChiller* chiller) : FloatItem(chiller)
{
  this->fermentChiller = chiller;
  selection = fermentChiller->rampStartTemp;
  active = true;
}
void RampStartTemp::getTitle(char* title)
{
  strncpy(title, "Start Temp", 16);
}
void RampStartTemp::getValue(char* value)
{
  if(selection == fermentChiller->rampStartTemp)
  {
    dtostrf((double)selection, 0, 1, value);
  }
  else
  {
    dtostrf((double)selection, 0, 1, value);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* RampStartTemp::click()
{
  fermentChiller->setRampStartTemp(selection);
  fermentChiller->setSetPoint(selection);
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
  selection = fermentChiller->rampStartTemp;
}

RampEndTemp::RampEndTemp(FermentChiller* chiller) : FloatItem(chiller)
{
  this->fermentChiller = chiller;
  selection = fermentChiller->rampEndTemp;
  active = true;
}
void RampEndTemp::getTitle(char* title)
{
  strncpy(title, "End Temp", 16);
}
void RampEndTemp::getValue(char* value)
{
  if(selection == fermentChiller->rampEndTemp)
  {
    dtostrf((double)selection, 0, 1, value);
  }
  else
  {
    dtostrf((double)selection, 0, 1, value);
    strncat(value, newSelect, 16 - strlen(newSelect));
  }
}
MenuItem* RampEndTemp::click()
{
  fermentChiller->setRampEndTemp(selection);
  //return to and inactivate ramp mode item
  return back()->back()->back()->back()->back();
}
MenuItem* RampEndTemp::back()
{
  reset();
  return MenuItem::back();
}
void RampEndTemp::reset()
{
  selection = fermentChiller->rampEndTemp;
}
