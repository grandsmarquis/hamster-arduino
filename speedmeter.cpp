
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

  if (values->current_time == 0)
    {
#ifdef DEBUG
      DEBUG_PRINT("Beginning to fill table");
#endif
      values->current_time = time;
      values->values[values->current].value = 0;
      values->values[values->current].time = time;
    }

  if (values->current_time + TIME_PERIOD < time)
    {
#ifdef DEBUG
      DEBUG_PRINT("Going to next timeperiod");
#endif
      if (time - _last_fall > 4 * TIME_PERIOD)
	{
	  values->state = INACTIVE;
	  return;
	}
      if (values->values[values->current].value > 0)
	{
	  values->current = values->current + 1;
	}
      values->values[values->current].value = 0;
      values->values[values->current].time = time;
      values->current_time = time;
    }
  
  
  if (values->current >=  MAX_VALUES)
    {
#ifdef DEBUG
      DEBUG_PRINT("Values is FULL!!");
#endif
      values->state = FULL;
      return;
    }
  /*
#ifdef DEBUG
  if (state == HIGH)
    DEBUG_PRINT("HIGH");
  else
    DEBUG_PRINT("LOW");
#endif
  */
  
  if (state != _previous_state && state == LOW)
    {
      _last_interval = time - _last_fall;
      _last_fall = time;      
      if (_last_interval > 100)
	{
#ifdef DEBUG
	  DEBUG_PRINT("We add one value");
#endif
	  values->values[values->current].value = values->values[values->current].value + 1;
	}
    }
  _previous_state = state;  
}

void SpeedMeter::clean(speed_values *values)
{
  values->state = EMPTY;
  values->current = 0;
  values->current_time = 0;

  int i = 0;
  while (i < MAX_VALUES)
    {
      values->values[i].time = 0;
      values->values[i].value = 0;
      i++;
    }
#ifdef DEBUG
  DEBUG_PRINT("Values are cleaned");
#endif
}
