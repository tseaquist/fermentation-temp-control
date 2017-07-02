#include "Info.h"
#include "../control/Chiller.h"
#include "Arduino.h"
#include "../util/stringutil.h"

class ChillerInfo : public Info
{
  public:
    Chiller* chiller;
    char title[17];
    char value[17];

  public:
    ChillerInfo(Chiller* chiller, const char* name);
    void displayInfo(LCD* lcd);
};
