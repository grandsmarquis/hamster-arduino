
#ifndef	__H_LIGHT__
#define	__H_LIGHT__

#include "main.hpp"

class Light {

private:
  int pin;
  
public:

  Light(int pin);
  void low();
  void high();
  void blink();
};

#endif
