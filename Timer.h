// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

/*
*	Simple Timer class based on millis(), does not watch for timer overflows since it is not expected that device runs thaht long
*/
class Timer {
private:
	unsigned long _TimeStarted = 0U; //when the timer was started

public:
	Timer(){ }

	bool IsStarted() {
		return (_TimeStarted != 0U);
	}

	/*
	+	returns time since the timer was started
	*/
	long GetTimePassed() {
		return millis() - _TimeStarted;
	}

	void Start() {
		_TimeStarted = millis();
	}

	float PercPassed(long pass) {
		return Math::clamp(GetTimePassed()/(float)pass,0.0f, 1.0f);
	}

	};

#else
	#include "WProgram.h"
#endif


#endif

