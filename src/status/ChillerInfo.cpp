#include "ChillerInfo.h"

ChillerInfo::ChillerInfo(Chiller* chiller, const char* title)
{
  this->chiller = chiller;
  this->title[0] = {0};
  this->value[0] = {0};
  strncpy(this->title, title, 16);
}

void ChillerInfo::displayInfo(LCD *lcd)
{
  float currentSetPoint = chiller->setPoint;
  float currentTemp = shorten(chiller->readTemp());

  char data[17] = "Temp:";
  dtostrf((double)currentTemp, 0, 1, data + strlen(data));
  //arrow ->
  strncat(data, "~", 16 - strlen(data));
  dtostrf((double)currentSetPoint, 0, 1, data + strlen(data));

  lcd->show(title, data);
}
