#include "ChillerMenuItems.h"
#include <MemoryFree.h>

ChillerMenuItem::ChillerMenuItem(Chiller* chiller):MenuItem()
{
  this->chiller = chiller;
  this->up = this;
}
void ChillerMenuItem::getTitle(char* title)
{
  title[0] = '\0';
  strncpy(title, chiller->name, 16);
  strncat(title, ": ", 16 - strlen(title));
  double temp = chiller->readTemp();
  if(temp > 50)
  {
    dtostrf((double)temp, 0, 1, title + strlen(title));
  }
  else
  {
    strncat(title, "NA", 16 - strlen(title));
  }
}
void ChillerMenuItem::getValue(char* value)
{
  value[0] = '\0';
  float setPoint = chiller->setPoint;
  strncpy(value, "SP: ", 16);
  dtostrf((double)setPoint, 0, 1, value + strlen(value));
}
MenuItem* ChillerMenuItem::turn(int count)
{
  if(count != 0) kill();
  return MenuItem::turn(count);
}
MenuItem* ChillerMenuItem::click()
{
  create();
  return MenuItem::click();
}
MenuItem* ChillerMenuItem::back()
{
  return this;
}
void ChillerMenuItem::kill()
{
  for(int i = 0; i < 3; i++)
  {
    if(itemList[i]!=NULL)
    {
      delete itemList[i];
      itemList[i] = NULL;
    }
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

void FermentorMenuItem::getValue(char *value)
{
  value[0] = '\0';
  float setPoint = chiller->setPoint;
  if(!fermentor->rampModeOn )
  {
    strncpy(value, "SP: ", 16);
    dtostrf((double)setPoint, 0, 1, value + strlen(value));
  }
  else
  {
    float endTemp = fermentor->rampEndTemp;
    int timeLeft = fermentor->rampTotalDuration_Hours - fermentor->rampCurrentDuration_Hours;
    dtostrf((double)setPoint, 0, 1, value + strlen(value));
    strncat(value, "~", 16 - strlen(value));
    dtostrf((double)endTemp, 0, 1, value + strlen(value));
    strncat(value, ": ", 16 - strlen(value));
    itoa(timeLeft, value + strlen(value), 10);
    strncat(value, "hr", 16 - strlen(value));
  }
}

void FermentorMenuItem::kill()
{
  ChillerMenuItem::kill();
  for(int i = 0; i < 4; i++)
  {
    if(rampList[i]!=NULL)
    {
      delete rampList[i];
      rampList[i] = NULL;
    }
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
  rampList[0]->up = this;

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
