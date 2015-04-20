
#include "common.hpp"

bool Common::joinAccessPoint(Storage *storage, Wifi *wifi)
{
  bool res = false;
  WifiCredentials wifiinfos;
  storage->getWifi(&wifiinfos);
  DEBUG_PRINT("__JOINING:"  );
  DEBUG_PRINT("SSID: " + String(wifiinfos.SSID));
  DEBUG_PRINT("PASSWORD: " + String(wifiinfos.password));
  res = wifi->joinAP(String(wifiinfos.SSID), String(wifiinfos.password));
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
      for (int i = 0; i < len; i++)
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
	  Serial.println(answer);
	  if (answer == "success")
	    return (true);
	  return (false);
	}
    }
  return (false);
}

bool Common::doAvailableRequest(Storage *storage, Wifi *wifi)
{
  bool res = false;

  String request = "PUT ";
  String content = "{\"device_key\" : \"" ;//+ storage->apikey;
  content += "\"}";
  request += "/products/" + String(String((char *) storage->getSerial()));
  request += " HTTP/1.1";
  request += "\nContent-Type: application/json";
  request += "\nContent-Length: ";
  request += String(content.length());
  request += "\n\n";
  request += content;
  String url = API_URL;
  Serial.println(url);
    Serial.println(request);
  if (wifi->createTCP(url, API_PORT))
    {
      delay(200);
      DEBUG_PRINT("[OK] creating connection to AvailableURL");
      if (wifi->send((const uint8_t*)request.c_str(), request.length()))
	{
	  DEBUG_PRINT("[OK] Sent request");
	}
      else
	{
	  DEBUG_PRINT("[FAIL] Sent request");
	}
      if (Common::readAnswer(storage, wifi))
	{
	  DEBUG_PRINT("[OK] SUCCESS SENDING AVAILABLE INFOS");
	}
      else
	{
	  DEBUG_PRINT("[FAIL] !!!!!");
	}
	
    }
  else
    {
      DEBUG_PRINT("[FAIL] creating connection to AvailableURL");
    }
  
}

bool Common::doRequest(Storage *storage, Wifi *wifi, String type, String request)
{
  
}
