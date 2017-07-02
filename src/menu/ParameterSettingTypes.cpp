#include "ParameterSettingTypes.h"

const char* newSelect = "?";
const char* notActive = "~";
const char* on = "ON";
const char* off = "OFF";

FloatItem::FloatItem(Chiller* chiller):MenuItem(chiller)
{
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

IntItem::IntItem(Chiller* chiller):MenuItem(chiller)
{
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

BoolItem::BoolItem(Chiller* chiller):MenuItem(chiller)
{
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
  return this;
}
MenuItem* SetPoint::back()
{
  if(active)
  {
    active = false;
    return this;
  }
  selection = chiller->setPoint;
  return MenuItem::back();
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
  return this;
}
MenuItem* Tolerance::back()
{
  if(active)
  {
    active = false;
    return this;
  }
  selection = chiller->tolerance;
  return MenuItem::back();
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
  return this;
}
MenuItem* CycleDuration::back()
{
  if(active)
  {
    active = false;
    return this;
  }
  selection = chiller->minCycleDuration_Minutes;
  return MenuItem::back();
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
    fermentChiller->setRampModeOn(selection);
    fermentChiller->setSetPoint(currentTemp);
    fermentChiller->setRampStartTemp(currentTemp);
    fermentChiller->setRampEndTemp(currentTemp + 5.0);
    fermentChiller->setRampCurrentDuration_Hours(0);
    fermentChiller->setRampTotalDuration_Hours(48);
    down->reset();
    return down;
  }
  else
  {
    active = false;
    return this;
  }
}
MenuItem* RampMode::back()
{
  if(active)
  {
    active = false;
    return this;
  }
  selection = chiller->minCycleDuration_Minutes;
  return MenuItem::back();
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
    Serial.println(selection);
    utoa(selection, value, 10);
    Serial.println(value);
  }
  else
  {
    Serial.println("new");
    Serial.println(selection);
    utoa(selection, value, 10);
    strncat(value, newSelect, 16 - strlen(newSelect));
    Serial.println(value);
  }
}
MenuItem* RampDuration::click()
{
  fermentChiller->setRampTotalDuration_Hours(selection);
  fermentChiller->setRampCurrentDuration_Hours(0);
  fermentChiller->previousCycleTime = millis();
  down->reset();
  return down;
}
MenuItem* RampDuration::back()
{
  selection = fermentChiller->rampTotalDuration_Hours;
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
  down->reset();
  return down;
}
MenuItem* RampStartTemp::back()
{
  if(active)
  {
    active = false;
    return this;
  }
  selection = fermentChiller->rampStartTemp;
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
  return up->up->up->back();
}
MenuItem* RampEndTemp::back()
{
  selection = fermentChiller->rampEndTemp;
  return MenuItem::back();
}
void RampEndTemp::reset()
{
  selection = fermentChiller->rampEndTemp;
}
