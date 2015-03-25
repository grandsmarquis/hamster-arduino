
#ifndef __H_WIFI__
#define __H_WIFI__

#include "ESP8266.h"

class		Wifi {

private:

  ESP8266 *wifi;

public:

  Wifi(HardwareSerial &serial);

  bool isAlive(void);
  String getVersion(void);
  
  bool createAP(String name, String password);
  String getIp(void);
  String getConnectedIPs();
    
};

#endif
