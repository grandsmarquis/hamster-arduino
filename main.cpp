
#include "main.hpp"
#include "speedmeter/speedmeter.hpp"
#include "wifi.hpp"

SpeedMeter *sensor;
Wifi	   *wifi;
bool	   hasClient = false;

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

void initAP()
{
  if (wifi->createAP("This is a testicule", "password"))
    Serial.println("[OK] Creating ap");
  else
    Serial.println("[FAIL] Creating ap");
  /*  if (wifi->reset())
    Serial.println("[OK] Reset");
  else
    Serial.println("[FAIL] Reset");
  */
  if (wifi->createTCPServer(8080, 10))
    Serial.println("[OK] Creating TCP Server");
  else
    Serial.println("[FAIL] Creating TCP Server");
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

void	setup()
{
  Serial.begin(9600);

  wifi = new Wifi(Serial1);

  ping();
  initAP();

     while (!hasClient)
    {
      String res = wifi->getConnectedIPs();
      Serial.println(res.c_str());
    }
  
  //  sensor = new SpeedMeter(2, 1, 10);
}



void	loop()
{
   receive();
  //sensor->update();
  //  Serial.print("Loop");
}
