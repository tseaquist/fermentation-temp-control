#include "ChillerMenuItems.h"
#include <MemoryFree.h>

ChillerMenuItem::ChillerMenuItem(Chiller* chiller):MenuItem(chiller)
{
  up = NULL;
}
void ChillerMenuItem::getTitle(char* title)
{
  strncpy(title, chiller->name, 16);
}
void ChillerMenuItem::getValue(char* value)
{
  strncpy(value, "~Settings", 16);
}
MenuItem* ChillerMenuItem::turn(int count)
{
  Serial.println(freeMemory());
  if(count != 0) kill();
  Serial.println(freeMemory());
  return MenuItem::turn(count);
}
MenuItem* ChillerMenuItem::click()
{
  Serial.println(freeMemory());
  create();
  Serial.println(freeMemory());
  return MenuItem::click();
}
MenuItem* ChillerMenuItem::back()
{
  kill();
  return NULL;
}
void ChillerMenuItem::kill()
{
  for(MenuItem* item : itemList)
  {
    delete item;
  }
}
void ChillerMenuItem::create()
{
  itemList[0] = new SetPoint(chiller);
  itemList[1] = new Tolerance(chiller);
  itemList[2] = new CycleDuration(chiller);

  this->down = itemList[0];

  for(int k = 0; k < 3; k++)
  {
    if(k > 0)
    {
      itemList[k]->left = itemList[k-1];
    }
    if(k < 2)
    {
      itemList[k]->right = itemList[k+1];
    }
    itemList[k]->up = this;
  }
}

FermentorMenuItem::FermentorMenuItem(FermentChiller* chiller):ChillerMenuItem(chiller)
{
  fermentor = chiller;
}
void FermentorMenuItem::kill()
{
  for(MenuItem* item : itemList)
  {
    delete item;
  }
  for(MenuItem* item : rampList)
  {
    delete item;
  }
}
void FermentorMenuItem::create()
{
  ChillerMenuItem::create();
  MenuItem* cycleDuration = itemList[2];

  rampList[0] = new RampMode(fermentor);
  rampList[1] = new RampDuration(fermentor);
  rampList[2] = new RampStartTemp(fermentor);
  rampList[3] = new RampEndTemp(fermentor);

  cycleDuration->right = rampList[0];
  rampList[0]->left = cycleDuration;

  for(int k = 0; k < 4; k++)
  {
    if(k > 0)
    {
      rampList[k]->up = rampList[k-1];
    }
    if(k < 3)
    {
      rampList[k]->down = rampList[k+1];
    }
  }
}
