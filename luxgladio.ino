


#ifndef CALIBRATION

#include "MPU6050_6Axis.h"
#include <Wire.h>
#include <SD.h>
#include "LightController.h"
#include "MotionController.h"
#include "SoundController.h"
#include "Math.h"
#include "Light.h"
#include "Timer.h"
#include "GladioDefines.h"
#include "Button.h"
#include "SaberStatus.h"

#define Debug

ESaberStatus _Status;
Button _Button;
MotionController _MotionController;
SoundController _SoundController;
LightController _LightController;
Timer _Timer;

void setup()
{

	/* add setup code here */


#ifdef DEBUG
	Serial.begin(SerialTransferRate);
#endif

	SetOff();
	
	//Setup SD
	//if (!SD.begin(PinSD)) {
		//Serial.println("initialization failed!");
	//}
	
	_MotionController.Initialize();
	Serial.println("initialization done.");

}

void loop()
{
	//Check Button Status First
	_Button.Loop();

	_MotionController.Loop();

	switch (_Status)
	{
	case Off:
		break;
	case On:
		break;
	case PowerOn:
	{
		float perc = _Timer.PercPassed(TimerIgnite);
		if (perc >= 1.0f) {
			SetOn();
		}
		else {
			_LightController.Ignite(perc);
		}
	}

	break;
	case PowerOff:
	{
		float perc = _Timer.PercPassed(TimerRetract);
		if (perc >= 1.0f) {
			SetOff();
		}
		else {
			_LightController.Retract(perc);
		}
	}
	break;
	case Clash:
	{
		float perc = _Timer.PercPassed(TimerClash);
		if (perc >= 1.0f) {
			SetHumming();
		}
		else {
			_LightController.Clash(perc);
		}
	}
	break;
	case Blaster:
		break;
	case LockUp:
		_LightController.LockUp(_Timer.GetTimePassed());
		break;
	case Swing:
		break;
	case Spin:
		break;
	default:
		break;
	}
}

void SetIgnite() {
	_Status = ESaberStatus::PowerOn;
	_Timer.Start();
	_SoundController.PlayIgnition();
	_Button.SetOnHold(nullptr);
	_Button.SetOnSingleClick(nullptr);
	_Button.SetOnDoubleClick(nullptr);
}

void SetRetract() {
	_Status = ESaberStatus::PowerOff;
	_Timer.Start();
	_SoundController.PlayRetraction();
	_Button.SetOnHold(nullptr);
	_Button.SetOnSingleClick(nullptr);
	_Button.SetOnDoubleClick(nullptr);
}

void PrepareLockUp() {
	SetLockUp();
}

void BlasterBlock() {
	SetClash();
}

void Settings() {

}

void BlueTooth() {

}

void SetLockUp() {
	_Status = ESaberStatus::LockUp;
	_Timer.Start();
	_SoundController.PlayLockUp();
}


void SetClash() {

	_Status = ESaberStatus::Clash;

	_Timer.Start();
	_SoundController.PlayClash();

}

void SetHumming() {

	_Status = ESaberStatus::On;

	_SoundController.PlayHumming();
	_LightController.On();
}


void SetOn() {

	_Status = ESaberStatus::On;

	_Button.SetOnHold(SetRetract);
	_Button.SetOnSingleClick(PrepareLockUp);
	_Button.SetOnDoubleClick(BlasterBlock);

	_LightController.On();
	_SoundController.PlayHumming();
}

void SetOff() {

	_Status = ESaberStatus::Off;

	_Button.SetOnSingleClick(SetIgnite);
	_Button.SetOnHold(Settings);
	_Button.SetOnDoubleClick(BlueTooth);


	_LightController.Off();
	_SoundController.StopPlayback();

}

#endif