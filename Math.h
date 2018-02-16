// Math.h

#ifndef _MATH_h
#define _MATH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"


class Math {
public:
	
	/*
	*	Clamp a Value between min and max
	*/
	template<class T>
	static T clamp(T value, T mi, T ma) {
		return max(mi, min(value, ma));
	}

	/*
	*	Converts a float value between 0.0f and 1.0f to a value between 0 and 255 (uint8_t)
	*/
	static uint8_t percToInt8(float a) {
		return (uint8_t)((clamp(a, 0.0f, 1.0f)) * 255);
	}

	/*
	*	Converts a uint8_t value between 0 and 255 to a float value between 0.0f (0U) and 1.0f (255U)
	*/
	static float int8ToPerc(uint8_t a) {
		return (((float)a) / 255.0f);
	}

	/*
	*	linear interpolation between 2 values
	*/
	template<class T>
	static T lerp(T start, T end, float percent) {
		return start + percent *  (end - start);
	}
	
};

#else
	#include "WProgram.h"
#endif


#endif

