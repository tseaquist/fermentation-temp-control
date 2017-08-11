#include "Menu.h"

Menu::Menu(TempControllers* controls, LCD* lcd)
{
  this->lcd = lcd;
  MenuItem* item = new FermentorMenuItem(controls->fermentChillers[0]);
  rootItem = item;
  currentItem = item;
  MenuItem* previousItem = item;
  for(int i = 1; i < controls->numFerments; i++)
  {
    item = new FermentorMenuItem(controls->fermentChillers[i]);
    item->left = previousItem;
    previousItem->right = item;
    previousItem = item;
  }
  item = new ChillerMenuItem(controls->chillerLiquid);
  item->left = previousItem;
  previousItem->right = item;
  previousItem = item;
  item = new ResetDefaults(controls);
  item->left = previousItem;
  previousItem->right = item;
  previousItem = item;
}

void Menu::update(int turnCount, bool rotaryClick, bool menuClick)
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

  display(currentItem);
}
void Menu::display(MenuItem* item)
{
  currentItem->getTitle(title);
  currentItem->getValue(value);
  lcd->show(title, value);
}
