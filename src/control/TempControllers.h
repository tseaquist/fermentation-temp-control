#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "FermentChiller.h"
// #include <vector>
using namespace std;

class TempControllers
{
  public:
    int const numFerments = 1;
    const char* names[1] = {"Tank A"};
    FermentChiller* fermentChillers[1];
    Chiller* chillerLiquid;

  public:
    TempControllers( );
    void update();
    void resetToDefault();
};

#endif
