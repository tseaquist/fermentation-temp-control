#include "MenuItem.h"
#include "../control/TempControllers.h"
#include "../display/LCD.h"
/*
Chiller, Fermentor 1, Fermentor 2, ..., Settings

Chiller -> SetPoint, Tolerance, MinCycleDuration

Fermentor i -> SetPoint, Tolerance, MinCycleDuration, Ramp i (on off)

Ramp i on -> (Fires choice selection menu)
          startTemp -> endTemp -> duration ->
*/

class Menu
{
  public:
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
