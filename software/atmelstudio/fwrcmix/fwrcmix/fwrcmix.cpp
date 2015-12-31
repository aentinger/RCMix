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

#include <avr/io.h>
#include <avr/interrupt.h>

#include "rcout.h"

/************************************************************************/
/* PROTOTYPES                                                           */
/************************************************************************/

void init_application();

/************************************************************************/
/* FUNCTIONS                                                            */
/************************************************************************/

int main(void)
{
	init_application();
	
	sei();
	
	RcOut::setRcOutState(RcOut::OUT1, RcOut::OUTx_ON);
	RcOut::setRcOutState(RcOut::OUT2, RcOut::OUTx_ON);
	RcOut::setRcOutState(RcOut::OUT3, RcOut::OUTx_ON);
	RcOut::setRcOutState(RcOut::OUT4, RcOut::OUTx_ON);
	RcOut::setRcOutState(RcOut::OUT5, RcOut::OUTx_ON);
	RcOut::setRcOutState(RcOut::OUT6, RcOut::OUTx_ON);
	
	RcOut::setPwmPulseDurationUs(RcOut::OUT1, 1000);
	RcOut::setPwmPulseDurationUs(RcOut::OUT2, 1500);
	RcOut::setPwmPulseDurationUs(RcOut::OUT3, 2000);
	RcOut::setPwmPulseDurationUs(RcOut::OUT4, 1000);
	RcOut::setPwmPulseDurationUs(RcOut::OUT5, 1500);
	RcOut::setPwmPulseDurationUs(RcOut::OUT6, 2000);
	
    for(;;)
    {
        
    }
}

void init_application()
{
	RcOut::begin();
}

/** 
 * \brief this interrupt is ececuted when a interrupt is triggered
 * for which no isr was installed - signal a failure in that case.
 */
ISR(BADISR_vect)
{
	
}