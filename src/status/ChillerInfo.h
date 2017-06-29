#include "Info.h"
#include "../control/Chiller.h"
#include "Arduino.h"
#include "../display/stringutil.h"

class ChillerInfo : public Info
{
  public:
    Chiller* chiller;
    char name[17];

  public:
    ChillerInfo(Chiller* chiller, const char* name);
    void displayInfo(LCD* lcd);
};
