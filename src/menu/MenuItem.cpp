#include "MenuItem.h"

MenuItem::MenuItem(const char* title)
{
  this->title[0] = '\0';
  setTitle(title);
  this->value[0] = '\0';
  left = this;
  right = this;
  up = this;
  down = this;
}

MenuItem::MenuItem(const char* title, const char* statusValue) : MenuItem(title)
{
  setContainerValue(statusValue);
}

void MenuItem::setTitle(const char *str)
{
  copyForLcd(title, str);
}

void MenuItem::setValue(const char *str)
{
  copyForLcd(value, str);
};

void MenuItem::setValueOption(const char* option)
{
  appendForLcd(value, "?", option);
}

void MenuItem::setContainerValue(const char* statusValue)
{
  prependForLcd(value, "~", statusValue);
}

void MenuItem::setLeft(MenuItem* item)
{
  left = item;
}
void MenuItem::setRight(MenuItem* item)
{
  right = item;
}
void MenuItem::setUp(MenuItem* item)
{
  up = item;
}
void MenuItem::setDown(MenuItem* item)
{
  down = item;
}

MenuItem* MenuItem::turn(int count)
{
  if(count == 0)
  {
    return this;
  }
  if(count > 0)
  {
    return right;
  }
  return left;
}
MenuItem* MenuItem::click()
{
  return down;
}
MenuItem* MenuItem::back()
{
  return up;
}
void MenuItem::reset()
{
  //do nothing on default
}
