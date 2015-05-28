
#ifndef	__H_MAIN__
#define	__H_MAIN__

#ifndef DRIVER
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

#define DEBUG		(1)
#define SERIAL_DEBUG	(Serial)

#define SERIAL_WIFI	(Serial1)

#define INTERRUPT_RESET	(1)
#define INTERRUPT_WHEEL	(0)

#define LIGHT_PIN	(13)

#define API_PORT	(3000)
#define API_URL		"89.3.174.175"

//#define API_PORT	(80)
//#define API_URL	"http://hamster-api.heroku.com/" ??

#define TIME_PERIOD	(5000)
#define MAX_VALUES	(5)
#define	MAX_TIME_SLEEP	(5)
#define MIN_VALUES_SEND	(2)

#define	WIFI_MAXTRY	(8)

typedef enum {
  SLEEP,
  INT_RESET,
  INT_HAMSTER,
  HAMSTER_COLLECT,
  HAMSTER_SENDING
} t_state;

#define DEBUG_PRINT(TEXT) SERIAL_DEBUG.println(TEXT)

void initEverything(void);
void wheelRisingInterrupt(void);
void resetButtonInterrupt(void);
void ping(void);

#endif
