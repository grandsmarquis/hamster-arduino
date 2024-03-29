
#include "setup.hpp"

bool  Setup::initAccessPoint(Storage *storage, Wifi *wifi)
{
  bool res;
  res = wifi->createAP("HAMSTER-SPINNER", "password");
  return (res);
}

bool    Setup::sendSerialNumber(Storage *storage, Wifi *wifi)
{
  uint32_t len = 8 + SERIAL_LEN + 2;
  char buffer[len];
  SerialNumber sn;

  storage->getSerial(&sn);
  strcpy(buffer, "SUCCESS:");
  strncpy(&(buffer[8]), (char *) sn.serial, SERIAL_LEN);
  buffer[len - 2] = '\n';
  buffer[len - 1] = 0;
  DEBUG_PRINT(buffer);
  return (wifi->send((const uint8_t*) buffer, len));
}

bool    Setup::receiveConnectionInformations(Storage *storage, Wifi *wifi)
{
  uint8_t buffer[128] = {0};
  uint32_t len;
  int state = 0;
  int pos = 0;
  String confirm;
  String id;
  String ssid;
  String password;

  while ((len =  wifi->receive(buffer, 120, 1000)))
    {
      buffer[len] = 0;
      String line((char *) buffer);
      for (uint32_t i = 0; i < len; i++)
	{
	  char c = (char) buffer[i];
	  Serial.println(c);
	  if (c == 0)
	    {
	      break;
	    }
	  else if (c == SETUP_DELIM_CHAR)
	    {
	      state++;
	    }
	  else if (state == 0)
	    {
	      confirm += c;
	    }
	  else if (state == 1)
	    {
	      id += c;
	    }
	  else if (state == 2)
	    {
	      ssid += c;
	    }
	  else if (state == 3)
	    {
	      password += c;
	    }
	  else
	    break;
	}
      if (state == 4)
	{
	  WifiCredentials w;
	  ssid.toCharArray((w.SSID), SSID_LEN);
	  password.toCharArray((w.password), PASSWORD_LEN);
	  id.toCharArray((w.apikey), API_LEN);
#ifdef DEBUG
	  DEBUG_PRINT(w.SSID);
	  DEBUG_PRINT(w.password);
	  DEBUG_PRINT(w.apikey);
#endif
	  storage->setWifi(&w);
	  return (true);
	}
     }
  
  return (false);
}

void Setup::doBinding(Storage *storage, Wifi *wifi, Light *light)
{
  String ip;
  bool hasConnection = false;

  Setup::initAccessPoint(storage, wifi);
  delay(1000);
  wifi->disableMUX();
  while (!hasConnection)
    {
      delay(1000);
#ifdef DEBUG
      DEBUG_PRINT("[Waiting] Waiting for connecting device");
#endif
      String res = wifi->getConnectedIPs();
      if (-1 != res.indexOf(','))
	{
	  delay(500);
	  ip = res.substring(0, res.indexOf(','));
#ifdef DEBUG
	  DEBUG_PRINT("[START] Try TCP with : " + ip);
#endif
	  if (wifi->createTCP(ip, SETUP_PORT))
	    hasConnection = true;
	}
    }
#ifdef DEBUG
  DEBUG_PRINT("[OK] We are connected");
#endif
  delay(500);
  while (!Setup::sendSerialNumber(storage, wifi))
    {
      delay(1000);
#ifdef DEBUG
      DEBUG_PRINT("[OK] SERIAL SENT");
#endif
    }
  while (!Setup::receiveConnectionInformations(storage, wifi))
    {
#ifdef DEBUG
      DEBUG_PRINT("[OK] Waiting to receive connection infos");
#endif
      delay(1000);
    }
  delay(500);
  wifi->releaseTCP();
  while (!wifi->isAlive())
    {

    }
  WifiCredentials wifiinfos;
  storage->getWifi(&wifiinfos);
  if (Common::TryToJoinAccessPoint(storage, wifi, light, &wifiinfos))
    {
    }
  else
    {
      return;
    }
  //if we are here we have a connection to the app
  //it means we have his IP and can receive and send datas throught TCP
#ifdef DEBUG
  DEBUG_PRINT("[OK] We try to make request");
#endif
  delay(1000);
  Common::doAvailableRequest(storage, wifi, &wifiinfos);
}
