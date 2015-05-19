
#include <avr/sleep.h>

#include "main.hpp"
#include "speedmeter.hpp"
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

speed_values values;

volatile t_state state = SLEEP;


void	ping()
{
  String version = wifi->getVersion();
#ifdef DEBUG
  DEBUG_PRINT("Version :: " + version);
#endif
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
#ifdef DEBUG
  SERIAL_DEBUG.begin(9600);
  DEBUG_PRINT("Start Everything");
#endif
  storage = new Storage();
  wifi = new Wifi(SERIAL_WIFI);
  light = new Light(LIGHT_PIN);
  sensor = new SpeedMeter(2, 1, 5);
  while (!wifi->isAlive())
    {
      
    }

  light->blink();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
#ifdef DEBUG
  DEBUG_PRINT("init everything was done");
#endif
}

void	setup()
{
  initEverything();

#ifdef DEBUG
  Tools::writeSerialNumber(storage, "SN-Lolilolol");
#endif
}

void	loop()
{
  switch (state) {

  case SLEEP:
#ifdef DEBUG
    DEBUG_PRINT("GOING TO SLEEP");
#endif
    attachInterrupt(INTERRUPT_RESET, resetButtonInterrupt, LOW);
    attachInterrupt(INTERRUPT_WHEEL, wheelRisingInterrupt, LOW);
    delay(500);
    sleep_mode();
    sleep_disable();
    detachInterrupt(INTERRUPT_RESET);
    detachInterrupt(INTERRUPT_WHEEL);
#ifdef DEBUG
    DEBUG_PRINT("GETTING BACK FROM SLEEP");
#endif
    break;
    
  case INT_RESET:
    state = SLEEP;
#ifdef DEBUG
    DEBUG_PRINT("INT FROM SETUP");
#endif
    light->blink();
    light->high();
    Setup::doBinding(storage, wifi, light);
    light->low();
    break;
    
  case INT_HAMSTER:
    state = HAMSTER_COLLECT;
#ifdef DEBUG
    DEBUG_PRINT("INT FROM HAMSTER");
#endif
    break;
    
  case HAMSTER_COLLECT:

    sensor->update(millis(), &values);

    if (values.state == FULL || values.state == INACTIVE)
      {
	state = HAMSTER_SENDING;
      }
    
    break;

  case HAMSTER_SENDING:
#ifdef DEBUG
    DEBUG_PRINT("TRY TO SEND");
#endif
    
    break;
  }

}
