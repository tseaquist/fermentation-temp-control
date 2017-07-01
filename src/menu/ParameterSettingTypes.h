#ifndef PARAMETER_ITEMS
#define PARAMETER_ITEMS

#include "MenuItem.h"
#include "../control/FermentChiller.h"
#include "../util/numutil.h"

class FloatItem : public MenuItem
{
  public:
    float selection;
    bool active;
    FloatItem(Chiller* chiller);
    virtual void getTitle(char* title);
    virtual void getValue(char* value);
    MenuItem* turn(int count);
};

class IntItem : public MenuItem
{
  public:
    unsigned int selection;
    bool active;
    IntItem(Chiller* chiller);
    virtual void getTitle(char* title);
    virtual void getValue(char* value);
    MenuItem* turn(int count);
};

class BoolItem : public MenuItem
{
  public:
    bool selection;
    bool active = false;
    BoolItem(Chiller* chiller);
    virtual void getTitle(char* title);
    virtual void getValue(char* value);
    MenuItem* turn(int count);
};

class SetPoint : public FloatItem
{
public:
  SetPoint(Chiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class Tolerance : public FloatItem
{
public:
  Tolerance(Chiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class CycleDuration : public IntItem
{
public:
  CycleDuration(Chiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class RampMode : public BoolItem
{
public:
  FermentChiller* fermentChiller;
  RampMode(FermentChiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class RampDuration : public IntItem
{
public:
  FermentChiller* fermentChiller;
  RampDuration(FermentChiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class RampStartTemp : public FloatItem
{
public:
  FermentChiller* fermentChiller;
  RampStartTemp(FermentChiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

class RampEndTemp : public FloatItem
{
public:
  FermentChiller* fermentChiller;
  RampEndTemp(FermentChiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
};

#endif
