#include "main.hpp"
#include "speedmeter/speedmeter.hpp"
#include "wifi.hpp"
#include "button.hpp"
#include "storage.hpp"

#include "setup.hpp"

SpeedMeter *sensor;
Wifi	   *wifi;
Storage	   *storage;



#define PORT    (31664)

void	receive()
{
  uint8_t buffer[128] = {0};
  uint8_t mux_id;
  uint32_t len = wifi->receive(&mux_id, buffer, sizeof(buffer), 100);

  if (len > 0) {
    Serial.print("Status:[");
    Serial.print(wifi->getIPStatus().c_str());
    Serial.println("]");

    Serial.print("Received from :");
    Serial.print(mux_id);
    Serial.print("[");
    for(uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
    //    wifi->releaseTCP(mux_id);
  }
}

void	ping()
{
   if (wifi->isAlive())
    Serial.println("[OK] Wifi is alive");
  else
    Serial.println("[FAIL] Wifi is not alive");
  String version = wifi->getVersion();
  Serial.println("Version :: " + version);
}

void	initEverything()
{
  Serial.begin(9600);

  storage = new Storage();
  wifi = new Wifi(Serial1);
  while (!wifi->isAlive())
    {
      
    }
}

void	doBinding()
{
  String ip;
  bool hasConnection = false;
  Setup::initAccessPoint(storage, wifi);
  delay(1000);
  while (!hasConnection)
    {
      delay(500);
      Serial.println("[Waiting] Waiting for connecting device");
      String res = wifi->getConnectedIPs();
      if (-1 != res.indexOf(','))
	{
	  delay(500);
	  ip = res.substring(0, res.indexOf(','));
	  Serial.println("[START] Try TCP with : " + ip);
	  if (wifi->createTCP(ip, PORT))
	    hasConnection = true;
	}
    }
  Serial.println("[OK] We are connected");
  delay(500);
  while (!Setup::sendSerialNumber(storage, wifi))
    {
      delay(1000);
      Serial.println("[OK] SERIAL SENT");
    }
  while (!Setup::receiveConnectionInformations(storage, wifi))
    {
      Serial.println("[OK] Waiting to receive connection infos");
      delay(1000);
    }
  //  Serial.println("[OK] connection infos received : " + storage->ssid + " " + storage->password);
  delay(2000);
  wifi->releaseTCP();
  
  //storage->ssid = "Numericable-9813";
  //storage->password = "CQDKRP7SV37C"; 
  //storage->ssid = "oOoOoOoO0OoOoO0oOoo0oOoOo000OoOo";
  //storage->password = "CALIFORNIA7CZK279";
  //  joinAP(storage->ssid, storage->password);
  //wifi->reset();
  while (!wifi->isAlive())
    {
      
    }
  while (!Common::joinAccessPoint(storage, wifi))
    {
      Serial.println("[FAIL] Connecting to SSID");
    }
  //if we are here we have a connection to the app
  //it means we have his IP and can receive and send datas throught TCP
  Serial.println("[OK] We try to make request");
  delay(1000);
  Common::doAvailableRequest(storage, wifi);
}

void	setup()
{
  initEverything();
  doBinding();
}

void	loop()
{
  //   receive();
  //sensor->update();
  //  Serial.print("Loop");
}
