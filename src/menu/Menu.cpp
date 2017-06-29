#include "Menu.h"
#include "MenuItemTypes.h"

Menu::Menu(TempControllers* controls, LCD* lcd)
{
  this->lcd = lcd;
  MenuItem* chillingLiquid = new MenuItem("Cooler");
  rootItem = chillingLiquid;
  rootItem->setContainerValue("Settings");
  chillingLiquid->setUp(NULL);
  MenuItem* previousItem = chillingLiquid;
  MenuItem* item;
  for(int i = 0; i < controls->numFerments; i++)
  {
    FermentChiller* chiller = controls->fermentChillers[i];
    char name[17] = "Fermentor ";
    const char* numStr = String(i + 1).c_str();
    strcat(name, numStr);
    item = new MenuItem(name);
    item->setContainerValue("Settings");
    previousItem->setRight(item);
    item->setLeft(previousItem);
    item->setUp(NULL);

    MenuItem* lastChillerItem = setChillerMenu(item, chiller);

    MenuItem* staticRampItem = new MenuItem("Ramp Mode", chiller->rampModeOn ? "ON" : "OFF");
    staticRampItem->setUp(item);
    staticRampItem->setLeft(lastChillerItem);
    lastChillerItem->setRight(staticRampItem);

    MenuItem* rampList[4];
    rampList[0] = new RampMode(chiller);
    rampList[1] = new RampDuration(chiller);
    rampList[2] = new RampStartTemp(chiller);
    rampList[3] = new RampEndTemp(chiller);

    staticRampItem->setDown(rampList[0]);
    rampList[0]->setUp(staticRampItem);

    for(int k = 0; k < 4; k++)
    {
      if(k > 0)
      {
        rampList[k]->setUp(rampList[k-1]);
      }
      if(k < 3)
      {
        rampList[k]->setDown(rampList[k+1]);
      }
    }
  }

  setChillerMenu(chillingLiquid, controls->chillerLiquid);

  onOff(false);
}

MenuItem* Menu::setChillerMenu(MenuItem* item, Chiller *chiller)
{
  MenuItem* staticItemList[3];
  staticItemList[0] = new MenuItem("Set Point", String(chiller->setPoint,1).c_str());
  staticItemList[1] = new MenuItem("Tolerance", String(chiller->tolerance, 1).c_str());
  staticItemList[2] = new MenuItem("Cycle Guard Mins", String(chiller->minCycleDuration_Minutes).c_str());

  MenuItem* setPoint = new SetPoint(chiller);
  MenuItem* tolerance = new Tolerance(chiller);
  MenuItem* cycleDuration = new CycleDuration(chiller);

  staticItemList[0]->setDown(setPoint);
  setPoint->setUp(staticItemList[0]);
  staticItemList[1]->setDown(tolerance);
  tolerance->setUp(staticItemList[1]);
  staticItemList[2]->setDown(cycleDuration);
  cycleDuration->setUp(staticItemList[2]);

  item->setDown(staticItemList[0]);

  for(int k = 0; k < 3; k++)
  {
    if(k > 0)
    {
      staticItemList[k]->setLeft(staticItemList[k-1]);
    }
    if(k < 2)
    {
      staticItemList[k]->setRight(staticItemList[k+1]);
    }
    staticItemList[k]->setUp(item);
  }

  return staticItemList[2];
}

void Menu::onOff( bool onOff)
{
  currentItem = rootItem;
  menuOn = onOff;
}

bool Menu::update(int turnCount, bool rotaryClick, bool menuClick)
{
  if(!menuOn)
  {
    if(menuClick)
    {
      onOff(true);
    }
    else
    {
      return false;
    }
  }
  else
  {
    if(menuClick)
    {
      currentItem = currentItem->back();
    }
    if(turnCount != 0)
    {
      currentItem = currentItem->turn(turnCount);
    }
    if(rotaryClick)
    {
      currentItem = currentItem->click();
    }
  }

  if(currentItem == NULL)
  {
    onOff(false);
    return false;
  }
  else
  {
    display(currentItem);
  }
  return true;
}
void Menu::display(MenuItem* item)
{
  lcd->show(item->title, item->value);
}

void Menu::exitMenu()
{
  //TODO decide if this is necesarry
}
