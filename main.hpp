

#ifndef DRIVER
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

#define BINDING_PORT	(31664)

#define HAS_DEBUG 0
#define SERIAL_DEBUG Serial

#define SERIAL_WIFI Serial1

#define DEBUG_PRINT(TEXT) if (HAS_DEBUG) { SERIAL_DEBUG.println(TEXT); }
