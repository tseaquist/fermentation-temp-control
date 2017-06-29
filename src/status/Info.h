#include "../display/LCD.h"
#include <math.h>
#include "../util/numutil.h"

class Info
{
  public:
    Info(){}
    virtual void displayInfo(LCD* lcd);
};
