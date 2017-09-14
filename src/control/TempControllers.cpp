#include "TempControllers.h"

TempControllers::TempControllers( )
{
  Thermistor* therm1 = new Thermistor(0, 10000, 0.001125308852122, 0.000234711863267, 0.0, 0.000000085663516);
  fermentChillers[2] = new FermentChiller(0, 6, therm1, "Tank C");
  Thermistor* therm2 = new Thermistor(1, 10000, 0.001125308852122, 0.000234711863267, 0.0, 0.000000085663516);
  fermentChillers[1] = new FermentChiller(1, 7, therm2, "Tank B");
  Thermistor* therm3 = new Thermistor(2, 10000, 0.001125308852122, 0.000234711863267, 0.0, 0.000000085663516);
  fermentChillers[0] = new FermentChiller(2, 8, therm3, "Tank A");
  Thermistor* thermChiller = new Thermistor(3, 10000, 0.001125308852122, 0.000234711863267, 0.0, 0.000000085663516);
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
