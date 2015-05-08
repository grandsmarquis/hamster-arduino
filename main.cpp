
#include <avr/sleep.h>

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
volatile t_state state = SLEEP;

#define PORT    (31664)

void	ping()
{
  String version = wifi->getVersion();
  DEBUG_PRINT("Version :: " + version);
}

void	wheelRisingInterrupt()
{
  state = INT_HAMSTER;
}

void	resetButtonInterrupt()
{
  state = INT_RESET;
}

void	initEverything()
{
  
  Serial.begin(9600);
  DEBUG_PRINT("initEverything");
  storage = new Storage();
  wifi = new Wifi(SERIAL_WIFI);
  light = new Light(LIGHT_PIN);

  while (!wifi->isAlive())
    {
      
    }

  light->blink();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  DEBUG_PRINT("initEverything");
}

void	setup()
{
  initEverything();
  Tools::writeSerialNumber(storage, "SN-Lolilolol");
}



void	loop()
{
  switch (state) {
  case SLEEP:
    DEBUG_PRINT("GOING TO SLEEP");
    attachInterrupt(INTERRUPT_RESET, resetButtonInterrupt, LOW);
    attachInterrupt(INTERRUPT_WHEEL, wheelRisingInterrupt, LOW);
    delay(500);
    sleep_mode();
    sleep_disable();
    detachInterrupt(INTERRUPT_RESET);
    detachInterrupt(INTERRUPT_WHEEL);
    DEBUG_PRINT("GETTING BACK FROM SLEEP");
    break;
  case INT_RESET:
    state = SLEEP;
    DEBUG_PRINT("BIND");
    light->blink();
    light->high();
    Setup::doBinding(storage, wifi, light);
    light->low();
    break;
  case INT_HAMSTER:
    state = SLEEP;
    DEBUG_PRINT("HAMSTER TURN");
    break;
  case HAMSTER_COLLECT:
    break;
  }

}
