#include <Arduino.h>

class Button
{
  protected:
    int buttonPin;
    int previousButtonState;

  public:
    Button(int buttonPin);
    bool isClicked();
};
