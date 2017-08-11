#include "Arduino.h"
#include "menu/Menu.h"
#include "input/Input.h"

TempControllers* controllers;
Menu* menu;
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
}

void loop()
{
  controllers->update();
  int turnCount = input->getTurnCount();
  bool rotaryClick = input->isRotaryClick();
  bool menuClick = input->isMenuClick();
  menu->update(turnCount, rotaryClick, menuClick);
}
