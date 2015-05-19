

#ifndef		__H_SPEEDMETER_
#define		__H_SPEEDMETER_

#include	"main.hpp"

typedef enum {
  EMPTY,
  INDETERMINATE,
  FULL,
  INACTIVE
}		speed_state;

typedef struct {
  int		time;
  int		value;
}		speed_instant;

typedef struct {
  int		current;
  unsigned long	current_time;
  speed_instant	values[MAX_VALUES];
  speed_state	state;
}		speed_values;

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

  SpeedMeter(int pin, int sensors, int radius);

  void update(unsigned long time, speed_values *values);
  void clean(speed_values *values);
};

#endif
