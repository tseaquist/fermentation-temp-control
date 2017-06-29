#include "TempControllers.h"

TempControllers::TempControllers( )
{
  for(int i = 0; i < numFerments; i++)
  {
    fermentChillers[i] = new FermentChiller(i);
  }
  chillerLiquid = new Chiller(numFerments);
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
