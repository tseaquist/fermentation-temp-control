#include "ResetDefaults.h"

ResetDefaults::ResetDefaults(TempControllers* controls) : MenuItem()
{
  this->controls = controls;
  status = "Reset?";
}
MenuItem* ResetDefaults::click()
{
  controls->resetToDefault();
  status = "Reset complete";
  return this;
}
MenuItem* ResetDefaults::turn(int count)
{
  reset();
  return MenuItem::turn(count);
}
void ResetDefaults::getTitle(char* title)
{
  strncpy(title, "Reset Parameters", 16);
}
void ResetDefaults::getValue(char* value)
{
  strncpy(value, status, 16);
}
void ResetDefaults::reset()
{
  status = "Reset?";
}
