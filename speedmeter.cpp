
#include "speedmeter.hpp"

SpeedMeter::SpeedMeter(int pin, int sensors, int radius)
  :_pin(pin), _sensors(sensors), _radius(radius), _previous_state(0), _speed(0.0), _distance(0.0),
   _last_fall(0), _last_interval(0)
{
  pinMode(_pin, INPUT);
}

void	SpeedMeter::update(unsigned long time, speed_values *values)
{
  int state = digitalRead(_pin);

  if (state != _previous_state && state == LOW)
    {
      _last_interval = time - _last_fall;
      _last_fall = time;

      if (values->current_time == 0)
	{
	  values->current_time = time;
	}
      else if (values->current_time + TIME_PERIOD < time)
	{
	  values->current = values->current + 1;
	}
      if (values->current > MAX_VALUES)
	{
	  //	  return (true);
	}
      values->values[values->current].value = values->values[values->current].value + 1;
      
      if (_last_interval > 100)
	{

	}
    }
  _previous_state = state;  
}

