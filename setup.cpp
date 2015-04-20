
#include "setup.hpp"

bool  Setup::initAccessPoint(Storage *storage, Wifi *wifi)
{
  bool res;
  res = wifi->createAP("HAMSTER-SPINNER", "password");
  if (res)
    Serial.println("[OK] Creating ap");
  else
    Serial.println("[FAIL] Creating ap");
  if (wifi->disableMUX())
    Serial.println("[OK] Disable MUX");
  else
    Serial.println("[FAIL] Disable Mux");
  return (res);
}

bool    Setup::sendSerialNumber(Storage *storage, Wifi *wifi)
{
  uint32_t len = 8 + SERIAL_LEN + 2;
  char buffer[len];

  strcpy(buffer, "SUCCESS:");
  strncpy(&(buffer[8]), (char *) storage->getSerial(), SERIAL_LEN);
  buffer[len - 2] = '\n';
  buffer[len - 1] = 0;
  Serial.print(buffer);
  return (wifi->send((const uint8_t*) buffer, strlen(buffer)));
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
      Serial.println("receive: ");
      buffer[len] = 0;
      String line((char *) buffer);
      Serial.println(line);
      for (int i = 0; i < len; i++)
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
	  //	  storage->ssid = ssid;
	  //	  storage->password = password;
	  //	  storage->apikey = id;
	  return (true);
	}
     }
  
  return (false);
}
