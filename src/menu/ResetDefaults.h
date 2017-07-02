#include "../control/TempControllers.h"
#include "MenuItem.h"

class ResetDefaults : public MenuItem
{
  public:
    TempControllers* controls;
    const char* status;
    ResetDefaults(TempControllers* controls);
    MenuItem* click();
    MenuItem* turn(int count);
    void getTitle(char* title);
    void getValue(char* value);
    void reset();
};
