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
