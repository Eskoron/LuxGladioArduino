// Light.h

#ifndef _LIGHT_h
#define _LIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "math.h"

/*
*	Represents 3 inviual pwm signal for 3 leds
*/
class Light {
public:
	uint8_t led_1;
	uint8_t led_2;
	uint8_t led_3;

public:
	Light(float led_1_perc, float led_2_perc, float led_3_perc) : led_1(Math::percToInt8(led_1_perc)), led_2(Math::percToInt8(led_2_perc)), led_3(Math::percToInt8(led_3_perc)) {
	}

	Light(uint8_t led_1, uint8_t led_2, uint8_t led_3) : led_1(led_1), led_2(led_2), led_3(led_3) {
	}

	Light(int led_1, int led_2, int led_3) : led_1(Math::clamp(led_1, 0, 255)), led_2(Math::clamp(led_2, 0, 255)), led_3(Math::clamp(led_3, 0, 255)) {

	}


	static Light lerp(Light a, Light b, float v) {

		return Light(Math::lerp((int)a.led_1, (int)b.led_1, v), Math::lerp((int)a.led_2, (int)b.led_2, v), Math::lerp((int)a.led_3, (int)b.led_3, v));

	}


	static Light peak(Light a, Light b, float v) {
		if (v <= 0.5) {
			v *= 2;
		}
		else {
			v = ((1 - v) * 2);
		}
		return Light(Math::lerp((int)a.led_1, (int)b.led_1, v), Math::lerp((int)a.led_2, (int)b.led_2, v), Math::lerp((int)a.led_3, (int)b.led_3, v));

	}

	static Light wave(Light a, Light b, long u) {
		const float pi = 3.14;
		const float frequency = 35; // Frequency in Hz
		return lerp(a, b, 0.5*(1 + sin(2.0f * pi * frequency * ((float)u))));
	}
};
#else
	#include "WProgram.h"
#endif


#endif

