
#include "wifi.hpp"

Wifi::Wifi(HardwareSerial &serial)
{
  wifi = new ESP8266(serial);
}

bool Wifi::isAlive(void)
{
  return (wifi->kick());
}

String Wifi::getVersion(void)
{
  return (wifi->getVersion());
}

bool Wifi::createAP(String name, String password)
{
  boolean res = wifi->setSoftAPParam(name, password);
  if (res)
    res = wifi->setOprToSoftAP();
  return (res);
}

String Wifi::getIp(void)
{
  String res = wifi->getLocalIP();
  return (res);
}

String Wifi::getConnectedIPs()
{
  String res = wifi->getJoinedDeviceIP();
  return (res);
}
