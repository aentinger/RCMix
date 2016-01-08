/**
 * \file led.cpp
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief class for controlling the used led
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "led.h"

#include "hal.h"

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief initialize the led module
 */
void Led::begin()
{
	initULed();
	
	Led::setState(LED_OFF);
}
	
/** 
 * \brief turn the led on or off
 */
void Led::setState(E_LED_STATE const state)
{
	switch(state)
	{
		case LED_ON: clearULed(); break;
		case LED_OFF: setULed(); break;
		default: setULed(); break;
	}
}