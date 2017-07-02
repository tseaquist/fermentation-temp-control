#include "../control/TempControllers.h"
#include "../display/LCD.h"
#include "ParameterSettingTypes.h"
#include "ChillerMenuItems.h"
#include "ResetDefaults.h"

class Menu
{
  public:
    char title[17] = {0};
    char value[17] = {0};

    bool menuOn;
    MenuItem* rootItem;
    MenuItem* currentItem;
    LCD* lcd;

  public:
    Menu(TempControllers* controls, LCD* lcd);
    MenuItem* setChillerMenu(MenuItem* item, Chiller *chiller);
    void onOff(bool onOff);
    bool update(int turnCount, bool rotaryClick, bool menuClick);
    void display(MenuItem* item);
    void exitMenu();
};
