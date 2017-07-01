#include "MenuItem.h"
#include "ParameterSettingTypes.h"

class ChillerMenuItem : public MenuItem
{
public:
  MenuItem* itemList[3] = {0};
  ChillerMenuItem(Chiller* chiller);
  void getTitle(char* title);
  void getValue(char* value);
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
  void kill();
  void create();
};
