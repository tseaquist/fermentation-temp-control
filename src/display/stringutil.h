#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Arduino.h>

void copyForLcd(char* dest, const char* str);

void prependForLcd(char* dest, const char* prepend, const char* str);

void appendForLcd(char* dest, const char* append, const char* str);

void concatForLcd(char* concatMe, const char* str);

int simplemin(int a, int b);

const char* toString(float val);
const char* toString(float val, int precision);
const char* toString(int val);
const char* toString(unsigned int val);
const char* toString(bool val);
