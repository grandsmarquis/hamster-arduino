#include "main.hpp"
#include "speedmeter/speedmeter.hpp"
#include "wifi.hpp"
#include "button.hpp"
#include "storage.hpp"
#include "light.hpp"

#include "setup.hpp"
#include "common.hpp"
#include "tools.hpp"

SpeedMeter *sensor;
Wifi	   *wifi;
Storage	   *storage;
Light	   *light;


#define PORT    (31664)

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
  light = new Light(2);
  
  while (!wifi->isAlive())
    {
      
    }
  attachInterrupt(INTERRUPT_RESET, resetButtonInterrupt, FALLING);
}

void	resetButtonInterrupt()
{
  Setup::doBinding(storage, wifi);
}

void	setup()
{
  initEverything();
  Tools::writeSerialNumber(storage, "SN-Lolilolol");
}

void	loop()
{
  //   receive();
  //sensor->update();
  //  Serial.print("Loop");
}
