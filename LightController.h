// LightController.h

#ifndef _LIGHTCONTROLLER_h
#define _LIGHTCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "SaberStatus.h"
#include "Light.h"
#include "GladioDefines.h"

class LightController {

	Light _Off = Light(0.0f, 0.0f, 0.0f);		//led configuration when saber is off
	Light _On = Light(0.1f, 1.0f, 1.0f);		//led configuration when saber is on
	Light _Clash = Light(0.4f, 1.0f, 1.0f);		//led configuration when saber clashes
	Light _LockUp = Light(0.3f, 0.8f, 0.8f);	//led condiguration when saberlockup
	Light _Blaster = Light(0.3f, 0.5f, 0.5f);	//led configuration for blaster deflect

public:

	LightController() {
		pinMode(PinLed1, OUTPUT);
		pinMode(PinLed2, OUTPUT);
		pinMode(PinLed3, OUTPUT);
		analogWrite(PinLed1, LOW);
		analogWrite(PinLed1, LOW);
		analogWrite(PinLed1, LOW);
	}
	

	void Off() {
		SetLight(_Off);
	}

	void On() {
		SetLight(_On);
	}

	void Ignite(float perc) {
		SetLight(Light::lerp(_Off,_On,perc));
	}

	void Retract(float perc) {
		SetLight(Light::lerp(_On, _Off, perc));
	}

	void Clash(float perc) {
		SetLight(Light::peak(_On, _Clash, perc));
	}

	void LockUp(unsigned long time) {
		SetLight(Light::wave(_On, _LockUp, time));
	}

private:
	void SetLight(Light light) {
		analogWrite(PinLed1, light.led_1);
		analogWrite(PinLed2, light.led_2);
		analogWrite(PinLed3, light.led_3);
	}
	

};
#else
	#include "WProgram.h"
#endif


#endif
