#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "Arduino.h"
#include "../display/stringutil.h"

class MenuItem
{
  public:
    char title[17];
    char value[17];
    MenuItem* left;
    MenuItem* right;
    MenuItem* up;
    MenuItem* down;

  public:
    MenuItem(const char* title);
    MenuItem(const char* title, const char* statusValue);

    void setTitle(const char* str);
    void setValue(const char* str);
    void setValueOption(const char* option);
    void setContainerValue(const char* statusValue);

    void setLeft(MenuItem* item);
    void setRight(MenuItem* item);
    void setUp(MenuItem* item);
    void setDown(MenuItem* item);

    virtual MenuItem* turn(int count);
    virtual MenuItem* click();
    virtual MenuItem* back();
    virtual void reset();
};

#endif
