/**
 * \file rcin.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief Interpret and decode up to 4 PWM input signals
 * \license 
 */

#ifndef RCIN_H_
#define RCIN_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef enum
{
	IN1 = 0, IN2 = 1, IN3 = 2, IN4 = 3
} E_RC_IN_SELECT;

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class RcIn
{

public:

	/** 
	 * \brief initialize thc RcIn module
	 */
	static void begin();
	
	/** 
	 * \brief returns true if the selected input channel has received valid signals
	 */
	static bool isGood(E_RC_IN_SELECT const sel);
	
	/** 
	 * \brief returns the duration of the pulses on the selected input channel
	 */
	static uint16_t getPulseDurationUs(E_RC_IN_SELECT const sel);

private:

	/** 
	 * \brief no public constructing
	 */	
	RcIn() { }
};


#endif /* RCIN_H_ */