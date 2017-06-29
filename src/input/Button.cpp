#include "Button.h"

Button::Button(int buttonPin)
{
  this->buttonPin = buttonPin;
  pinMode(buttonPin, INPUT);
  previousButtonState = LOW;
}

bool Button::isClicked()
{
  // read the state of the pushbutton value:
  bool isClicked = false;
  int buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && previousButtonState == LOW) {
    isClicked = true;
    //debounce
    delay(250);
  }
  previousButtonState = buttonState;
  return isClicked;
}
