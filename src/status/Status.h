#include "../control/TempControllers.h"
#include "Arduino.h"
#include "../display/LCD.h"
#include "ChillerInfo.h"

class Status
{
  public:
    TempControllers* tempControllers;
    LCD* lcd;
    Info* info[1];

  public:
    Status(TempControllers* tempControllers, LCD* lcd);
    void update();
};
