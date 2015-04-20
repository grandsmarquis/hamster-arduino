
#include "light.hpp"

Light::Light(int p)
  : pin(p)
{
  pinMode(pin, OUTPUT);
}

void Light::low()
{
  digitalWrite(pin, LOW);
}

void Light::high()
{
  digitalWrite(pin, HIGH);
}
