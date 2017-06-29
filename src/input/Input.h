#include "RotaryDial.h"
#include "Button.h"

class Input
{
  public:
    RotaryDial dial;
    Button rotaryButton;
    Button menuButton;

  public:
    Input();

    int getTurnCount();
    bool isRotaryClick();
    bool isMenuClick();
};
