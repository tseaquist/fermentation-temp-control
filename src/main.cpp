#include "Arduino.h"
#include "menu/Menu.h"
#include "status/Status.h"
#include "input/Input.h"

TempControllers* controllers;
Menu* menu;
Status* status;
LCD* lcd;
Input* input;

bool menuOn;

void setup()
{
  Serial.begin(9600);
  input = new Input();
  lcd = new LCD();
  controllers = new TempControllers();
  // controllers->resetToDefault();
  menu = new Menu(controllers, lcd);
  menuOn = menu->menuOn;
  status = new Status(controllers, lcd);
}

void loop()
{
  controllers->update();
  int turnCount = input->getTurnCount();
  bool rotaryClick = input->isRotaryClick();
  bool menuClick = input->isMenuClick();
  if(turnCount != 0 || rotaryClick || menuClick)
  {
    menuOn = menu->update(turnCount, rotaryClick, menuClick);
  }
  if(!menuOn)
  {
    status->update(turnCount);
  }
}
