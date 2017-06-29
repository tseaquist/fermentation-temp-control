#include "MenuItem.h"
#include "../control/FermentChiller.h"
#include "../util/numutil.h"

class SetPoint : public MenuItem
{
  public:
    float selection;
    Chiller* chiller;
    SetPoint(Chiller* chiller);
    ~SetPoint();
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class Tolerance : public MenuItem
{
  public:
    float selection;
    Chiller* chiller;
    Tolerance(Chiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class CycleDuration : public MenuItem
{
  public:
    int selection;
    Chiller* chiller;
    CycleDuration(Chiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class RampMode : public MenuItem
{
  public:
    bool selection;
    FermentChiller* chiller;
    RampMode(FermentChiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class RampStartTemp : public MenuItem
{
  public:
    float selection;
    FermentChiller* chiller;
    RampStartTemp(FermentChiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class RampEndTemp : public MenuItem
{
  public:
    float selection;
    FermentChiller* chiller;
    RampEndTemp(FermentChiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};

class RampDuration : public MenuItem
{
  public:
    unsigned int selection;
    FermentChiller* chiller;
    RampDuration(FermentChiller* chiller);
    MenuItem* turn( int count );
    MenuItem* click();
    MenuItem* back();
    void reset();
};
