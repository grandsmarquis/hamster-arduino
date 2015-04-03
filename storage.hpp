
#ifndef	__H_STORAGE__
#define	__H_STORAGE__

#include "Arduino.h"

#define	SERIAL_LEN 8


class		Storage {
  
private:
  uint8_t serial[SERIAL_LEN] = {'0', '0', '0', '0', '0', '0', '0', '0'};
  
public:

  Storage();
  uint8_t *getSerial();
  
};

#endif
