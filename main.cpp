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
  light = new Light(LIGHT_PIN);
  
  while (!wifi->isAlive())
    {
      
    }
  attachInterrupt(INTERRUPT_RESET, resetButtonInterrupt, RISING);
}

void	resetButtonInterrupt()
{
  light->blink();
  light->high();
  delay(500);
  Setup::doBinding(storage, wifi);
  light->blink();
  light->blink();
  light->low();
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
