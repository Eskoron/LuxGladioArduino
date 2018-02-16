// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "GladioDefines.h"

enum EButtonState : uint8_t {
	Idle,Pressed,OnceClicked,DoublePressed,HoldIdle
};

class Button {

private:

	void(*_OnSingleClick)(void) = nullptr;

	void(*_OnDoubleClick)(void) = nullptr;

	void(*_OnHold)(void) = nullptr;

	EButtonState _State;

	Timer _Timer;

public:

	void Loop() {
		if (_Timer.GetTimePassed() < ButtonDebounceTimer) {
			return;
		}
		long curButtonState = digitalRead(PinButton);

		switch (_State)
		{
		case Idle:
			//Button Is Clicked so set to Pressed State
			if (curButtonState == HIGH) {
				_Timer.Start();
				_State = EButtonState::Pressed;
			}
			//Button not Clicked
			else {
			}
			break;

		case Pressed:
			if (curButtonState == HIGH) {
				//Check how Long the Button is Pressed if it is longer than the hold button thrashold, dispatch onhold event;
				if (_Timer.GetTimePassed() >= ButtonHoldTimer) {
					_State = EButtonState::HoldIdle;
					break;
				}
				//Else do nothing
				else {
				}
			}
			//Button is Released so it is at least a click
			else {
				_State = EButtonState::OnceClicked;
				_Timer.Start();
			}

			break;

		case OnceClicked:

			//Check if we recognize it as a One Time Click event if time passed is bigger than Trashhold we recognize a Single Click
			if (_Timer.GetTimePassed() >= ButtonDoubleClickTimer) {
				Dispatch(_OnSingleClick);
			}
			else {
				//if the Button is Clicked we release 
				if (curButtonState == HIGH) {
					_State = EButtonState::DoublePressed;
					_Timer.Start();
				}
			}

			break;

		case DoublePressed:
			if (curButtonState == LOW) {

				Dispatch(_OnDoubleClick);
			}
			break;
		case HoldIdle:
			if (curButtonState == LOW) {
				Dispatch(_OnHold);
			}
			break;
		default:
			break;
		}
	}

	void SetOnSingleClick(void(*function)(void)) {
		_OnSingleClick = function;
	}

	void SetOnDoubleClick(void(*function)(void)) {
		_OnDoubleClick = function;
}

	void SetOnHold(void(*function)(void)) {
		_OnHold = function;
	}

private:
	void Reset() {
		_Timer.Start();
		_State = EButtonState::Idle;
	}

	void Dispatch(void(*function)(void)) {
		if (function != nullptr) {
			function();
		}
		Reset();
	}

};


#else
	#include "WProgram.h"
#endif


#endif

