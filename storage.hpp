
#ifndef	__H_STORAGE__
#define	__H_STORAGE__

#include "Arduino.h"
#include "EEPROM.h"

#define	SERIAL_LEN 14

#define SSID_LEN 40
#define PASSWORD_LEN 40
#define API_LEN 40

struct WifiCredentials {
  char SSID[SSID_LEN];
  char password[PASSWORD_LEN];
  char apikey[API_LEN];
};

struct SerialNumber {
  char serial[SERIAL_LEN];
};

class		Storage {
  
private:
  uint8_t serial[SERIAL_LEN] = {'S', 'N', '-', 'R', 'J', 'L', '3', '7', '0', 'J', 'O', 'U', '8', 0};

  
public:
  

  
  Storage();
  uint8_t *getSerial();

  void getWifi(WifiCredentials *wifi);
  void setWifi(WifiCredentials *wifi);
  void getSerial(SerialNumber *sn);
  void setSerial(SerialNumber *sn);
  
  void read(int address, char *buffer, int len);
  void write(int address, char *buffer, int len);
  
};

#endif
