

#ifndef		__H_SPEEDMETER_
#define		__H_SPEEDMETER_

#include	"../main.hpp"

class		SpeedMeter {

 private:
  
  int		_pin;
  int		_sensors;
  float		_radius;

  int		_previous_state;
  
  float		_speed;
  float		_distance;

  unsigned long	_last_fall;
  unsigned long	_last_interval;
  
 public:

  /*
  ** pin : digital pin
  ** sensors: number of sensors on wheel
  ** radius: radius of the wheel (cm)
  */
  SpeedMeter(int pin, int sensors, int radius);

  void update();
  
};

#endif
