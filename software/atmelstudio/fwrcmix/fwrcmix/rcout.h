/**
 * \file rcout.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief control up to 6 PWM outputs for generating rc pwm signals (20 ms period, pulse duration between 1 and 2 ms)
 * \license 
 */

#ifndef RCOUT_H_
#define RCOUT_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class RcOut
{

public:

	/** 
	 * \brief initialize the RcOut class (setup the timers, etc.)
	 */
	static void begin();
	
	typedef enum
	{
		OUT1 = 0, OUT2 = 1, OUT3 = 2, OUT4 = 3, OUT5 = 4, OUT6 = 5
	} E_RC_OUT_SELECT;	
	
	typedef enum
	{
		OUTx_ON, OUTx_OFF
	} E_RC_OUT_STATE;
	
	/** 
	 * \brief turn an output either on or off - off outputs have constant LOW level (0 V)
	 */
	static void setRcOutState(E_RC_OUT_SELECT const sel, E_RC_OUT_STATE const state);
	
	/** 
	 * \brief set the pulse duration of a desired rc mixer output
	 */
	static void setPwmPulseDurationUs(E_RC_OUT_SELECT const sel, uint16_t const pulse_duration_us);
	
private:

	/** 
	 * \brief no public Constructing
	 */
	RcOut() { }

};

#endif /* RCOUT_H_ */