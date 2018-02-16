// SaberStatus.h

#ifndef _SABERSTATUS_h
#define _SABERSTATUS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

enum ESaberStatus :  uint8_t{
	Off,On,PowerOn,PowerOff,Clash,Blaster,LockUp,Swing,Spin
};

#else
	#include "WProgram.h"
#endif


#endif

