#include "MenuItem.h"

MenuItem::MenuItem( Chiller* chiller )
{
  this->chiller = chiller;
  left = this;
  right = this;
  up = this;
  down = this;
}

MenuItem* MenuItem::turn(int count)
{
  if(count == 0)
  {
    return this;
  }
  if(count > 0)
  {
    return right;
  }
  return left;
}
MenuItem* MenuItem::click()
{
  return down;
}
MenuItem* MenuItem::back()
{
  return up;
}
