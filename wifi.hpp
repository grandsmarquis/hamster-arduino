
#ifndef __H_WIFI__
#define __H_WIFI__

#include "ESP8266.h"

class		Wifi {

private:

  ESP8266 *wifi;

public:

  Wifi(HardwareSerial &serial);

  // DEVICE
  bool		isAlive(void);
  bool		reset(void);
  String	getVersion(void);
  String	getIPStatus(void);
  bool		enableMUX(void);
  bool		disableMUX(void);
  
  //AP JOIN
  bool		joinAP(String name, String password);
  String	getAPList(void);
  String	getLocalIP(void);
  
  //AP CREATE
  bool		createAP(String name, String password);
  String	getIp(void);
  String	getConnectedIPs(void);

  // TCP
  bool		createTCP(String addr, uint32_t port);
  bool		releaseTCP(void);
  bool		createTCPServer(int port, int timeout);
  bool		stopTCPServer(void);
  bool		releaseTCP(uint8_t mux_id);
  uint32_t	receive(uint8_t *mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = 1000);
};

#endif
