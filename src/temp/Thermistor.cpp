#include "Thermistor.h"

Thermistor::Thermistor(unsigned int pin, double resistor, double A1, double A2, double A3, double A4)
{
  this->pin = pin;
  this->resistor = resistor;
  this->steinhartA1 = A1;
  this->steinhartA2 = A2;
  this->steinhartA3 = A3;
  this->steinhartA4 = A4;

  //Take the pin out of pull-up mode.
  //Arduino analog pins are 14-19 when accessed in digital mode.
  pinMode(14 + pin, INPUT);
  digitalWrite(14 + pin, LOW);
  //Throw away first read.
  analogRead(pin);

  lastUpdate = millis();
  update();
}

double Thermistor::getResistance()
{
  unsigned int adc = analogRead(pin);
  double v = adc * voltage / (double) bitResolution;
  double resistance = voltage * resistor / v - resistor;
  return resistance;
}

float Thermistor::getTemp()
{
  unsigned long now = millis();
  if(now - lastUpdate > 1000)
  {
    lastUpdate = now;
    update();
  }
  return lastTemp;
}

void Thermistor::update()
{
  double resistance = getResistance();
  double lnResitance = log(resistance); // no reason to calculate this multiple times.
  //Build up the number in the stages.
  double temp = steinhartA4;
  temp = temp * lnResitance + steinhartA3;
  temp = temp * lnResitance + steinhartA2;
  temp = temp * lnResitance + steinhartA1;
  //Final part is to invert
  temp = 1.0 / temp;
  lastTemp = (float)(9.0 * (temp - 273.0) / 5.0 + 32.0);
  Serial.print("Temp:");
  Serial.print(lastTemp);
  Serial.print(", Resistance:");
  Serial.println(resistance);
}
