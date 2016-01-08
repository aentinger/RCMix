/**
 * \file control_demo.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief This class demonstrates a simple mixer where the four inputs are 1:1 mixed to four outputs (OUT1 = IN1, OUT2 = IN2, ...) including how to implement a failsafe
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "control_demo.h"

#include <stdbool.h>

#include "rcin.h"
#include "rcout.h"

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief this function returns true when all signals used in this specific mixer are good
 */
bool ControlDemo::isGoodFunc()
{
	return RcIn::isGood(IN1) && RcIn::isGood(IN2) && RcIn::isGood(IN3) && RcIn::isGood(IN4);
}

/** 
 * \brief this function implements the failsafe behaviour of this specific mixer
 */
void ControlDemo::failsafeFunc()
{
	RcOut::setRcOutState(OUT1, OUTx_OFF);
	RcOut::setRcOutState(OUT2, OUTx_OFF);
	RcOut::setRcOutState(OUT3, OUTx_OFF);
	RcOut::setRcOutState(OUT4, OUTx_OFF);
}

/** 
 * \brief this function implements the mixing behavior (function fOUT(IN1, IN2, ...) of this specific mixer
 */
void ControlDemo::mixingFunc()
{
	RcOut::setRcOutState(OUT1, OUTx_ON);
	RcOut::setRcOutState(OUT2, OUTx_ON);
	RcOut::setRcOutState(OUT3, OUTx_ON);
	RcOut::setRcOutState(OUT4, OUTx_ON);
			
	RcOut::setPwmPulseDurationUs(OUT1, RcIn::getPulseDurationUs(IN1));
	RcOut::setPwmPulseDurationUs(OUT2, RcIn::getPulseDurationUs(IN2));
	RcOut::setPwmPulseDurationUs(OUT3, RcIn::getPulseDurationUs(IN3));
	RcOut::setPwmPulseDurationUs(OUT4, RcIn::getPulseDurationUs(IN4));
}