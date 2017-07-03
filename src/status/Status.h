#include "../control/TempControllers.h"
#include "Arduino.h"
#include "../display/LCD.h"
#include "ChillerInfo.h"

class Status
{
  public:
    TempControllers* tempControllers;
    LCD* lcd;
    int index;

  public:
    Status(TempControllers* tempControllers, LCD* lcd);
    void update(int count);
    void turn(int count);
};
