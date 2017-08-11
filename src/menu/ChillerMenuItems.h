#include "MenuItem.h"
#include "ParameterSettingTypes.h"

class ChillerMenuItem : public MenuItem
{
public:
  MenuItem* itemList[3] = {0};
  Chiller* chiller;
  ChillerMenuItem(Chiller* chiller);
  virtual ~ChillerMenuItem(){}
  void getTitle(char* title);
  virtual void getValue(char* value);
  MenuItem* turn(int count);
  MenuItem* click();
  MenuItem* back();
  virtual void kill();
  virtual void create();
};

class FermentorMenuItem : public ChillerMenuItem
{
public:
  MenuItem* rampList[4] = {0};
  FermentChiller* fermentor;
  FermentorMenuItem(FermentChiller* chiller);
  ~FermentorMenuItem(){};
  void getValue(char* value);
  void kill();
  void create();
};
