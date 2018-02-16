// SoundController.h

#ifndef _SOUNDCONTROLLER_h
#define _SOUNDCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "TMRpcm.h"
#include "GladioDefines.h"

class SoundController {

private:
	TMRpcm _TMRpcm;

public:

	SoundController() {
		_TMRpcm.speakerPin = PinSpeaker;
		_TMRpcm.CSPin = PinSD;
	}

	void PlayIgnition() {
		_TMRpcm.loop(false);
		_TMRpcm.play("on.wav");
	}

	void PlayRetraction() {
		_TMRpcm.loop(false);
		_TMRpcm.play("off.wav");
	}

	void PlayHumming() {
		_TMRpcm.loop(true);
		_TMRpcm.play("hum.wav");
		
	}

	void PlayClash() {
		_TMRpcm.loop(false);
		_TMRpcm.play("clash.wav");
	}

	void PlaySpin() {
		
		_TMRpcm.loop(true);
	}

	void PlaySwing() {
		_TMRpcm.loop(true);
	}

	void PlayLockUp() {
		_TMRpcm.loop(true);
		_TMRpcm.play("lock.wav");
	}

	void StopPlayback() {
		_TMRpcm.stopPlayback();
	}

};
#else
	#include "WProgram.h"
#endif


#endif

