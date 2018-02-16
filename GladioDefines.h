// GladioDefines.h

#ifndef _GLADIODEFINES_h
#define _GLADIODEFINES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

//Pins

#define PinButton 2
#define PinSpeaker 9
#define PinSD 4
#define PinLed1 3
#define PinLed2 5
#define PinLed3 6

//Button Timer values in milliseconds
#define ButtonHoldTimer 1000 //ms  button push time needed until hold event is dispatched
#define ButtonDoubleClickTimer 250 //ms maximum time to recognize a double click  between 2 clicks
#define ButtonDebounceTimer 20 //ms to prevent clickering

//MPU6050 invidual Offset Value
#define AccelXOffset 5111
#define AccelYOffset -6293
#define AccelZOffset 9042
#define GyroXOffset 256
#define GyroYOffset 102
#define GyroZOffset -21

#define TimerIgnite 1000
#define TimerRetract 1000
#define TimerBlaster 100
#define TimerClash 1000


#else
	#include "WProgram.h"
#endif


#endif

