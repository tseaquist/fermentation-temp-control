#include "Input.h"

Input::Input():
  dial(3, 2),
  rotaryButton(4),
  menuButton(5)
{
  dial.getTurnCount();
  rotaryButton.isClicked();
  menuButton.isClicked();
}

int Input::getTurnCount()
{
  return dial.getTurnCount();
}

bool Input::isRotaryClick()
{
  return rotaryButton.isClicked();
}

bool Input::isMenuClick()
{
  return menuButton.isClicked();
}
