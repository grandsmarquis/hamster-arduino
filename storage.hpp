
#ifndef	__H_STORAGE__
#define	__H_STORAGE__

#include "Arduino.h"
#include "EEPROM.h"

#define	SERIAL_LEN 14

#define SSID_LEN 40
#define PASSWORD_LEN 40

struct WifiCredentials {
  char SSID[SSID_LEN];
  char PASSWORD[PASSWORD_LEN];
};

class		Storage {
  
private:
  uint8_t serial[SERIAL_LEN] = {'S', 'N', '-', 'R', 'J', 'L', '3', '7', '0', 'J', 'O', 'U', '8', 0};

  
public:
  

  
  Storage();
  uint8_t *getSerial();

  void getWifi(WifiCredentials *wifi);
  void read(int address, char *buffer, int len);
  void write(int address, char *buffer, int len);
  
};

#endif
