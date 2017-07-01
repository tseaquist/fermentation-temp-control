#include "Menu.h"

Menu::Menu(TempControllers* controls, LCD* lcd)
{
  this->lcd = lcd;
  MenuItem* chillingLiquid = new ChillerMenuItem(controls->chillerLiquid);
  rootItem = chillingLiquid;
  currentItem = chillingLiquid;
  MenuItem* previousItem = chillingLiquid;
  MenuItem* item;
  for(int i = 0; i < controls->numFerments; i++)
  {
    item = new FermentorMenuItem(controls->fermentChillers[i]);
    item->left = previousItem;
    previousItem->right = item;
    previousItem = item;
  }

  onOff(false);
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
  currentItem->getTitle(title);
  currentItem->getValue(value);
  lcd->show(title, value);
}

void Menu::exitMenu()
{
  //TODO decide if this is necesarry
}
