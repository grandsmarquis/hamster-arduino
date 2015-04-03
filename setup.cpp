
#include "setup.hpp"

bool  Setup::initAccessPoint(Storage *storage, Wifi *wifi)
{
  bool res;
  res = wifi->createAP("HAMSTER_00001", "password");
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
  uint32_t len = 3 + SERIAL_LEN + 1;
  char buffer[len];

  strcpy(buffer, "ok:");
  strncpy(&(buffer[3]), (char *) storage->getSerial(), SERIAL_LEN);
  buffer[len - 1] = 0;
  Serial.print(buffer);
  return (wifi->send((const uint8_t*) buffer, strlen(buffer)));
}

bool    Setup::receiveConnectionInformations(Storage *storage, Wifi *wifi)
{
  uint8_t buffer[128] = {0};
  uint32_t len = wifi->receive(buffer, sizeof(buffer), 127);
  char state = 0;
  int pos = 0;
  String confirm;
  String ssid;
  String password;
  
  if (len > 0) {
    buffer[0] = 0;
    String line((char *) buffer);
    for (uint32_t i = 0; i < len; i++)
      {
	char c = buffer[i];
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
	    ssid += c;
	  }
	else if (state == 2)
	  {
	    password += c;
	  }
	else
	  break;
      }
    Serial.println(confirm);
    Serial.println(ssid);
    Serial.println(password);
    storage->ssid = ssid;
    storage->password = password;
    return true;
  }
  
  return (false);
}
