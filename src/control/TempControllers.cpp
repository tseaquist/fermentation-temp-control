#include "TempControllers.h"

TempControllers::TempControllers( )
{
  Thermistor* therm2 = new Thermistor(0, 9845,
    1.0381149079075397E-3,
    2.5144581342720644E-4,
    0.0,
    0.0);
  fermentChillers[2] = new FermentChiller(0, 6, therm2, "Tank C");

  Thermistor* therm1 = new Thermistor(1, 9791,
    1.0381149079075397E-3,
    2.5144581342720644E-4,
    0.0,
    0.0);
  fermentChillers[1] = new FermentChiller(1, 7, therm1, "Tank B");

  Thermistor* therm0 = new Thermistor(2, 9719,
    1.0381149079075397E-3,
    2.5144581342720644E-4,
    0.0,
    0.0);
  fermentChillers[0] = new FermentChiller(2, 8, therm0, "Tank A");

  Thermistor* thermChiller = new Thermistor(3, 9769,
    1.0222846949397243E-3,
    2.5316455696202533E-4,
    0.0,
    0.0);
  chillerLiquid = new Chiller(numFerments, 9, thermChiller, "Chiller");
}

void TempControllers::update()
{
  for(int i = 0; i < numFerments; i++)
  {
    fermentChillers[i]->update();
  }
  chillerLiquid->update();
}

void TempControllers::resetToDefault()
{
  for(int i = 0; i < numFerments; i++)
  {
    fermentChillers[i]->setRampModeOn(false);
    fermentChillers[i]->setSetPoint(65);
    fermentChillers[i]->setTolerance(1);
    fermentChillers[i]->setMinCycleDuration_Minutes(1);
  }
  chillerLiquid->setSetPoint(45);
  chillerLiquid->setTolerance(5);
  chillerLiquid->setMinCycleDuration_Minutes(5);
}
