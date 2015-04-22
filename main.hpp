
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

#define BINDING_PORT	(31665)

#define HAS_DEBUG	(1)
#define SERIAL_DEBUG	(Serial)

#define SERIAL_WIFI	(Serial1)

#define INTERRUPT_RESET	(0)

#define LIGHT_PIN	4

#define DEBUG_PRINT(TEXT) if (HAS_DEBUG) { SERIAL_DEBUG.println(TEXT); }

void initEverything(void);
void resetButtonInterrupt(void);
void ping(void);

#endif
