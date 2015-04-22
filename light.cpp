
#include "light.hpp"

Light::Light(int p)
  : pin(p)
{
  pinMode(pin, OUTPUT);
  this->low();
}

void Light::low()
{
  digitalWrite(pin, LOW);
}

void Light::high()
{
  digitalWrite(pin, HIGH);
}

void Light::blink()
{
  this->high();
  delay(500);
  this->low();
  delay(500);
  this->high();
  delay(500);
  this->low();
}
