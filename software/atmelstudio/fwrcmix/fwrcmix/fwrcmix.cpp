/**
 * \file fwrcmic.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief Main file for the firmware of the rc mixer
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "led.h"
#include "rcin.h"
#include "rcout.h"
#include "control.h"

#include "config.h"
#ifdef CONFIG_USE_CONTROL_DEMO
#include "control_demo.h"
#endif

/************************************************************************/
/* PROTOTYPES                                                           */
/************************************************************************/

void init_application();

/************************************************************************/
/* FUNCTIONS                                                            */
/************************************************************************/

int main(void)
{
	Control control(
#ifdef CONFIG_USE_CONTROL_DEMO
	ControlDemo::isGoodFunc, ControlDemo::failsafeFunc, ControlDemo::mixingFunc
#endif
	);

	init_application();
	
	for(;;)
    {
		control.execute();
    }
}

/** 
 * \brief init the application
 */
void init_application()
{
	Led::begin();

	RcIn::begin();
	
	RcOut::begin();

	sei();
}

/** 
 * \brief this interrupt is executed when a interrupt is triggered
 * for which no isr was installed - signal a failure in that case.
 */
ISR(BADISR_vect)
{
	for(;;)
	{
		_delay_ms(50);
		Led::setState(LED_ON);
		_delay_ms(50);
		Led::setState(LED_OFF);
	}
}