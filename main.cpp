#include "main.hpp"
#include "speedmeter/speedmeter.hpp"
#include "wifi.hpp"
#include "button.hpp"
#include "storage.hpp"

#include "setup.hpp"

SpeedMeter *sensor;
Wifi	   *wifi;
Storage	   *storage;



#define PORT    (8090)
#define IP   "192.168.4.100"

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

void joinAP(String name, String password)
{
  if (wifi->joinAP(name, password))
    Serial.println("[OK] Joined AP");
  else
    Serial.println("[FAIL] Joined AP");
  Serial.print("IP: ");
  Serial.println(wifi->getLocalIP().c_str());  
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
  boolean hasConnection = false;
  
  Setup::initAccessPoint(storage, wifi);
  while (!hasConnection)
    {
      delay(500);
      Serial.println("[Waiting] Waiting for connecting device");
      String res = wifi->getConnectedIPs();
      if (-1 != res.indexOf(','))
	{
	  delay(1000);
	  Serial.println("[START] Try TCP");
	  ip = res.substring(0, res.indexOf(','));
	  if (wifi->createTCP(ip, PORT))
	    hasConnection = true;
	}
    }
  Serial.println("[OK] We are connected");
  while (true)
    {
      delay(1000);
      if (Setup::sendSerialNumber(storage, wifi))
	{
	  Serial.println("[OK] SERIAL SENT");
	}
    }
  while (!Setup::receiveConnectionInformations(storage, wifi))
    {
      Serial.println("[OK] Waiting to receive connection infos");
      delay(100);
    }
  Serial.println("[OK] connection infos received");
  joinAP(storage->ssid, storage->password);
  //if we are here we have a connection to the app
  //it means we have his IP and can receive and send datas throught TCP
  
}

void	setup()
{
  initEverything();
  doBinding();
}

void	loop()
{
   receive();
  //sensor->update();
  //  Serial.print("Loop");
}
