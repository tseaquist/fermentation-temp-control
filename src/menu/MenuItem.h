#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "Arduino.h"
#include "../util/stringutil.h"
#include "../control/Chiller.h"

class MenuItem
{
  public:
    MenuItem* left;
    MenuItem* right;
    MenuItem* up;
    MenuItem* down;

  public:
    MenuItem();
    virtual ~MenuItem(){};

    virtual void getTitle(char* title) {};
    virtual void getValue(char* value) {};

    virtual MenuItem* turn(int count);
    virtual MenuItem* click();
    virtual MenuItem* back();
    virtual void reset(){};
};

#endif
