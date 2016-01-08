/**
 * \file control.cpp
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief This class implements switching between failsafe and mixing mode as well as calling 
 * the concrete failsafe and mixing functions of your control implementation
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "control.h"

#include <util/delay.h>

#include "led.h"

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief The Constructor is handed over function pointers which point to the 
 * concrete implementation of the desired mixing functionality.
 */ 
Control::Control(controlIsGoodFunc isGoodFunc, controlFailsafeFunc failsafeFunc, controlMixingFunc mixingFunc)
: _isGoodFunc(isGoodFunc), _failsafeFunc(failsafeFunc), _mixingFunc(mixingFunc)
{
	
}
	
/** 
 * \brief This function is executed in the main loop. Here we call the 
 * concrete failsafe and mixing functions and accomplish the state 
 * transition between those states.
 */
void Control::execute()
{
	switch(_state)
	{
		case FAILSAFE:
		{
			if(_failsafeFunc != 0)
			{
				_failsafeFunc();
			}
			
			/* Signal failsafe state */
			
			toogleLed();
			
			_delay_ms(100);
			
			/* State handling */
			
			if(isGood())
			{
				_state = MIXING;
			}			
		}
		break;
		case MIXING:
		{
			if(_mixingFunc != 0)
			{
				_mixingFunc();
			}
			
			/* Signal active state */
			
			turnLedOn();
			
			/* State handling */
			
			if(!isGood())
			{
				_state = FAILSAFE;
			}
		}
		break;
		default:
		{
			_state = FAILSAFE;
		}
		break;
	}
}

/************************************************************************/
/* PRIVATE FUNCTIONS	                                                */
/************************************************************************/

bool Control::isGood()
{
	if(_isGoodFunc)
	{
		return _isGoodFunc();
	}
	else
	{
		return false;
	}
}

void Control::toogleLed()
{
	static bool is_led_turned_on = true;
				
	if(is_led_turned_on)
	{
		Led::setState(LED_ON);
	}
	else
	{
		Led::setState(LED_OFF);
	}
				
	is_led_turned_on = !is_led_turned_on;
}

void Control::turnLedOn()
{
	Led::setState(LED_ON);
}