#include "Status.h"

Status::Status(TempControllers* tempControllers, LCD* lcd)
{
  this->tempControllers = tempControllers;
  this->lcd = lcd;
  index = 0;
}
void Status::update(int count)
{
    turn(count);
    Chiller* chiller = index < 0 ? tempControllers->chillerLiquid : tempControllers->fermentChillers[index];
    FermentChiller* ferm = index < 0 ? NULL : tempControllers->fermentChillers[index];
    char row1[17] = {0};
    strncpy(row1, chiller->name, 16);
    strncat(row1, ":", 16 - strlen(row1));
    double temp = chiller->readTemp();
    dtostrf((double)temp, 0, 1, row1 + strlen(row1));

    char row2[17] = {0};
    float setPoint = chiller->setPoint;
    if(ferm == NULL || !ferm->rampModeOn )
    {
      strncpy(row2, "Set Pnt:", 16);
      dtostrf((double)setPoint, 0, 1, row2 + strlen(row2));
    }
    else
    {
      float endTemp = ferm->rampEndTemp;
      int timeLeft = ferm->rampTotalDuration_Hours - ferm->rampCurrentDuration_Hours;
      dtostrf((double)setPoint, 0, 1, row2 + strlen(row2));
      strncat(row2, "~", 16 - strlen(row2));
      dtostrf((double)endTemp, 0, 1, row2 + strlen(row2));
      strncat(row2, ":", 16 - strlen(row2));
      itoa(timeLeft, row2 + strlen(row2), 10);
      strncat(row2, "hrs", 16 - strlen(row2));
    }
    lcd->show(row1, row2);
}
void Status::turn(int count)
{
  index += count;
  index = index < -1 ? -1 : index;
  int n = tempControllers->numFerments - 1;
  index = index > n ? n : index;
}
