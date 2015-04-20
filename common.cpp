
#include "common.hpp"

bool Common::joinAccessPoint(Storage *storage, Wifi *wifi)
{
  bool res = false;
  //  Serial.println("__JOINING:"  );
  //  Serial.println("SSID: " + storage->ssid);
  //  Serial.println("PASSWORD: " + storage->password  );
  // res = wifi->joinAP(storage->ssid, storage->password);
  if (res)
    Serial.println("[OK] Joined AP");
  else
    Serial.println("[FAIL] Joined AP");
  if (res)
    {
      Serial.print("IP: ");
      Serial.println(wifi->getLocalIP().c_str());
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
      Serial.println("receive: ");
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
      Serial.println("[OK] creating connection to AvailableURL");
      if (wifi->send((const uint8_t*)request.c_str(), request.length()))
	{
	  Serial.println("[OK] Sent request");
	}
      else
	{
	  Serial.println("[FAIL] Sent request");
	}
      if (Common::readAnswer(storage, wifi))
	{
	  Serial.println("[OK] SUCCESS SENDING AVAILABLE INFOS");
	}
      else
	{
	  Serial.println("[FAIL] !!!!!");
	}
	
    }
  else
    {
      Serial.println("[FAIL] creating connection to AvailableURL");
    }
  
}

bool Common::doRequest(Storage *storage, Wifi *wifi, String type, String request)
{
  
}
