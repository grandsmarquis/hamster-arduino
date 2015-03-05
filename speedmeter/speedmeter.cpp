
#include "speedmeter.hpp"

SpeedMeter::SpeedMeter(int pin, int sensors, int radius)
  :_pin(pin), _sensors(sensors), _radius(radius), _previous_state(0), _speed(0.0), _distance(0.0),
   _last_fall(0), _last_interval(0)
{
  pinMode(_pin, INPUT);
}

void	SpeedMeter::update()
{
  int state = digitalRead(_pin);

  if (state != _previous_state && state == LOW)
    {
      _last_interval = millis() - _last_fall;
      _last_fall = millis();
      _speed = (_radius / (float) _last_interval) * 360.0; //Something like this
      Serial.println(_speed);
      
    }
  _previous_state = state;
  
}
