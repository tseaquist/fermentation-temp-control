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
    virtual ~FloatItem(){};
    virtual void getTitle(char* title){};
    virtual void getValue(char* value){};
    virtual void reset(){};
    MenuItem* turn(int count);
};

class IntItem : public MenuItem
{
  public:
    unsigned int selection;
    bool active;
    IntItem(Chiller* chiller);
    virtual ~IntItem(){};
    virtual void getTitle(char* title){};
    virtual void getValue(char* value){};
    virtual void reset(){};
    MenuItem* turn(int count);
};

class BoolItem : public MenuItem
{
  public:
    bool selection;
    bool active = false;
    BoolItem(Chiller* chiller);
    virtual ~BoolItem(){};
    virtual void getTitle(char* title){};
    virtual void getValue(char* value){};
    virtual void reset(){};
    MenuItem* turn(int count);
};

class SetPoint : public FloatItem
{
public:
  SetPoint(Chiller* chiller);
  ~SetPoint(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class Tolerance : public FloatItem
{
public:
  Tolerance(Chiller* chiller);
  ~Tolerance(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class CycleDuration : public IntItem
{
public:
  CycleDuration(Chiller* chiller);
  ~CycleDuration(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class RampMode : public BoolItem
{
public:
  FermentChiller* fermentChiller;
  RampMode(FermentChiller* chiller);
  ~RampMode(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class RampDuration : public IntItem
{
public:
  FermentChiller* fermentChiller;
  RampDuration(FermentChiller* chiller);
  ~RampDuration(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class RampStartTemp : public FloatItem
{
public:
  FermentChiller* fermentChiller;
  RampStartTemp(FermentChiller* chiller);
  ~RampStartTemp(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

class RampEndTemp : public FloatItem
{
public:
  FermentChiller* fermentChiller;
  RampEndTemp(FermentChiller* chiller);
  ~RampEndTemp(){};
  void getTitle(char* title);
  void getValue(char* value);
  MenuItem* click();
  MenuItem* back();
  void reset();
};

#endif
