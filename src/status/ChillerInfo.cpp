#include "ChillerInfo.h"

ChillerInfo::ChillerInfo(Chiller* chiller, const char* name)
{
  this->chiller = chiller;
  this->name[0] = '\0';
  copyForLcd(this->name, name);
}

void ChillerInfo::displayInfo(LCD *lcd)
{
  float currentSetPoint = chiller->setPoint;
  float currentTemp = shorten(chiller->readTemp());

  char data[17] = "Temp:";
  concatForLcd(data, String(currentTemp, 1).c_str());
  //arrow ->
  concatForLcd(data, "~");
  concatForLcd(data, String(currentSetPoint, 1).c_str());

  lcd->show(name, data);
}
