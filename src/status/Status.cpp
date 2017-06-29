#include "Status.h"

Status::Status(TempControllers* tempControllers, LCD* lcd)
{
  this->tempControllers = tempControllers;
  this->lcd = lcd;
  info[0] = new ChillerInfo(tempControllers->chillerLiquid, "Cooler");
}
void Status::update()
{
    info[0]->displayInfo(lcd);
  // String line1 = "AC Temp: ";
  // float chillerTemp = tempControllers->chillerLiquid->readTemp();
  // line1.concat(String(chillerTemp,1));
  // String line2 = "Ferm Temp: ";
  // float fermTemp = tempControllers->fermentChillers[0]->readTemp();
  // line2.concat(String(fermTemp, 1));
  // lcd->show(line1, line2);
}
