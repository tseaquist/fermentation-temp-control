#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "../util/stringutil.h"

class LCD
{
  public:
    LiquidCrystal_I2C lcd;
    unsigned long lastUpdate;
    char currentLine1[17];
    char currentLine2[17];

  public:
    LCD();
    void show(const char* line1, const char* line2);
};
#endif
