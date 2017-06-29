#include "stringutil.h"

void copyForLcd(char* dest, const char* str)
{
  int length = strlen(str);
  strncpy(dest, str, 16);
  for(int i = length; i < 16; i++)
  {
    dest[i] = ' ';
  }
  dest[16] = '\0';
}

void prependForLcd(char* dest, const char* prepend, const char* str)
{
  int preLength = strlen(prepend);
  int strLength = strlen(str);
  for(int i = 0; i < simplemin(preLength, 16); i++)
  {
    dest[i] = prepend[i];
  }
  for(int i = preLength; i < simplemin(preLength + strLength, 16); i++)
  {
    dest[i] = str[i - preLength];
  }

  int last = simplemin(preLength + strLength, 16);
  dest[last] = '\0';
}

void appendForLcd(char* dest, const char* append, const char* str)
{

  prependForLcd(dest, str, append);
}

void concatForLcd(char* concatMe, const char* str)
{
  int myLength = strlen(concatMe);
  if(myLength >= 16) return;
  strncat(concatMe, str, 16 - myLength);
  concatMe[16] = '\0';
}

char fltstr[5] = "";
const char* toString(float val)
{
  dtostrf((double)val, 0, 1, fltstr);
  return fltstr;
}

char fltpstr[17] = "";
const char* toString(float val, int precision)
{
  dtostrf((double)val, 0, precision, fltpstr);
  return fltpstr;
}

char intstr[5] = "";
const char* toString(int val)
{
  itoa(val, intstr, 10);
  return intstr;
}

char unsgnintstr[5] = "";
const char* toString(unsigned int val)
{
  utoa(val, unsgnintstr, 10);
  return unsgnintstr;
}

char onstr[3] = "ON";
char offstr[4] = "OFF";
const char* toString(bool val)
{
  return val ? onstr : offstr;
}

int simplemin(int a, int b)
{
  return a < b ? a : b;
}
