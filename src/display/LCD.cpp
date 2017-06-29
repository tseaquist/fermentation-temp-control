#include "LCD.h"
#include <Arduino.h>

LCD::LCD() : lcd(0x3F, 16, 2)
{
  lcd.begin();
  lcd.setBacklight( true );
  currentLine1[0] = '\0';
  currentLine2[0] = '\0';
}

void LCD::show(const char* line1, const char* line2)
{
    char test1[17];
    char test2[17];
    copyForLcd(test1, line1);
    copyForLcd(test2, line2);
    if(strcmp(test1, currentLine1) != 0)
    {
      copyForLcd(currentLine1, line1);
      lcd.setCursor(0, 0);
      lcd.print(currentLine1);
    }
    if(strcmp(test2, currentLine2) != 0)
    {
      copyForLcd(currentLine2, line2);
      lcd.setCursor(0, 1);
      lcd.print(currentLine2);
    }
}
