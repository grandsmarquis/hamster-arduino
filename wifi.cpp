
#include "wifi.hpp"

Wifi::Wifi(HardwareSerial &serial)
{
  wifi = new ESP8266(serial);
}

bool Wifi::isAlive(void)
{
  return (wifi->kick());
}

bool Wifi::reset(void)
{
  return (wifi->restart());
}

String Wifi::getVersion(void)
{
  return (wifi->getVersion());
}

bool Wifi::createAP(String name, String password)
{
  boolean res = wifi->setOprToSoftAP();
  if (res)
    res = wifi->setSoftAPParam(name, password);
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

bool Wifi::enableMUX()
{
  return (wifi->enableMUX());
}

bool Wifi::disableMUX()
{
  return (wifi->disableMUX());
}

bool Wifi::createTCPServer(int port, int timeout)
{
  bool res = this->enableMUX();
  if (res)
    {
      res = wifi->startTCPServer(port);
    }
  if (res)
    {
      res = wifi->setTCPServerTimeout(timeout);
    }
  return (res);
}

bool Wifi::stopTCPServer()
{
  return (wifi->stopTCPServer());
}

String Wifi::getIPStatus()
{
  return (wifi->getIPStatus());
}

bool Wifi::releaseTCP(uint8_t mux_id)
{
  return (wifi->releaseTCP(mux_id));
}

uint32_t Wifi::receive(uint8_t *mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
  return (wifi->recv(mux_id, buffer, sizeof(buffer), timeout));
}

bool Wifi::joinAP(String name, String password)
{
  boolean res = wifi->setOprToStation();
  if (res)
    res = wifi->joinAP(name, password);
  return (res);
}

String Wifi::getLocalIP()
{
  return (wifi->getLocalIP());
}

String Wifi::getAPList()
{
  return (wifi->getAPList());
}

