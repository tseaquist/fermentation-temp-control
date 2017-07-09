#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include "../temp/Thermistor.h"
#include "FermentChiller.h"
// #include <vector>
using namespace std;

class TempControllers
{
  public:
    int numFerments;
    FermentChiller* fermentChillers[1];
    Chiller* chillerLiquid;

  public:
    TempControllers( );
    void update();
    void resetToDefault();
};

#endif
