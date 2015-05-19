
#include "common.hpp"

bool Common::joinAccessPoint(Storage *storage, Wifi *wifi, WifiCredentials *wifiinfos)
{
  bool res = false;
#ifdef DEBUG
  DEBUG_PRINT("__JOINING:"  );
  DEBUG_PRINT("SSID: " + String(wifiinfos->SSID));
  DEBUG_PRINT("PASSWORD: " + String(wifiinfos->password));
#endif
  res = wifi->joinAP(String(wifiinfos->SSID), String(wifiinfos->password));
#ifdef DEBUG
  if (res)
    {
      DEBUG_PRINT("[OK] Joined AP");
    }
  else
    {
      DEBUG_PRINT("[FAIL] Joined AP");
    }
  if (res)
    {
      DEBUG_PRINT(wifi->getLocalIP().c_str());
    }
#endif
  wifi->disableMUX();
  return (res);  
}

bool Common::readAnswer(Storage *storage, Wifi * wifi)
{
  uint8_t buffer[128] = {0};
  uint32_t len;
  int state = 0;
  int pos = 0;
  String answer;

  while ((len =  wifi->receive(buffer, 120, 1000)))
    {
      buffer[len] = 0;
      String line((char *) buffer);
      Serial.println(line);
      for (uint32_t i = 0; i < len; i++)
	{
	  char c = (char) buffer[i];
	  Serial.println(c);
	  if (c == '"')
	    {
	      state++;
	    }
	  else if (state == 1)
	    {
	      answer += c;
	    }
	  else
	    break;
	}
      if (state >= 2)
	{
#ifdef DEBUG
	  DEBUG_PRINT(answer);
#endif
	  if (answer == "success")
	    return (true);
	  return (false);
	}
    }
  return (false);
}

bool Common::doAvailableRequest(Storage *storage, Wifi *wifi, WifiCredentials *wifiinfos)
{
  bool res = false;
  
  
  String request = "POST ";
  {
    SerialNumber sn;
    storage->getSerial(&sn);
    request += "/products/" + String(sn.serial);    
  }

  request += "HTTP/1.1";
  String content = "{\"device_key\" : \"" + String(wifiinfos->apikey);
  content += "\"}";
  request += "\n";
  request += "Host: ";
  request += API_URL;
  request += "\nContent-Type: application/json";
  request += "\nContent-Length: ";
  request += String(content.length());
  request += "\n\n";
  request += content;
  String url = API_URL;
#ifdef DEBUG
  DEBUG_PRINT(url);
  DEBUG_PRINT(request);
#endif
  if (wifi->createTCP(url, API_PORT))
    {
      delay(200);
      DEBUG_PRINT("[OK] creating connection to AvailableURL");
      wifi->send((const uint8_t*)request.c_str(), request.length());
      res = Common::readAnswer(storage, wifi);
    }
  else
    {
#ifdef DEBUG
      DEBUG_PRINT("[FAIL] creating connection to AvailableURL");
#endif
    }
  return (res);
}

bool Common::TryToJoinAccessPoint(Storage *storage, Wifi *wifi, Light *light, WifiCredentials *wifiinfos)
{
  int tries = 0;
  
  while (tries < WIFI_MAXTRY)
    {
      if (Common::joinAccessPoint(storage, wifi, wifiinfos))
	  return (true);
      tries++;
    }
  return (false);
}

bool Common::doRequest(Storage *storage, Wifi *wifi, String type, String request)
{

  return (true);
}

bool Common::tryToSendValues(Storage *storage, Wifi *wifi, Light *light, speed_values *values)
{
  WifiCredentials wifiinfos;
  
  storage->getWifi(&wifiinfos);
  if (Common::TryToJoinAccessPoint(storage, wifi, light, &wifiinfos))
    {
      return (true);
    }
  else
    {
      return false;
    }
  
}
