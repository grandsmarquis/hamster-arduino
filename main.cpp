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
    DEBUG_PRINT(wifi->getIPStatus().c_str());

    DEBUG_PRINT("Received from :");
    DEBUG_PRINT(mux_id);
    for(uint32_t i = 0; i < len; i++) {
      DEBUG_PRINT((char)buffer[i]);
    }
    //    wifi->releaseTCP(mux_id);
  }
}

void	ping()
{
  String version = wifi->getVersion();
  DEBUG_PRINT("Version :: " + version);
}

void	initEverything()
{
  Serial.begin(9600);

  storage = new Storage();
  wifi = new Wifi(SERIAL_WIFI);
  while (!wifi->isAlive())
    {
      
    }
}

void	setup()
{
  initEverything();
  Setup::doBinding(storage, wifi);
}

void	loop()
{
  //   receive();
  //sensor->update();
  //  Serial.print("Loop");
}
