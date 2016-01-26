/**
 * \file control_omnidrive_3_wheels.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief This class is mixing three channels for controlling a robot with omnidirectional drive via a remote control.
 * \license 
 */

#ifndef OMNIDRIVE_3_WHEELS_H_
#define OMNIDRIVE_3_WHEELS_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#ifdef CONFIG_USE_CONTROL_OMNIDRIVE_3_WHEELS

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class ControlOmnidrive3Wheels
{

public:

	/** 
	 * \brief this function returns true when all signals used in this specific mixer are good
	 */
	static bool isGoodFunc();
	
	/** 
	 * \brief this function implements the failsafe behavior of this specific mixer
	 */
	static void failsafeFunc();
	
	/** 
	 * \brief this function implements the mixing behavior (function fOUT(IN1, IN2, ...) of this specific mixer
	 */
	static void mixingFunc();
	
	/** 
	 * \brief this function implements the behaviour if a transition from mixing to failsafe is taking place
	 */
	static void transitionToFailsafeFunc();
	
	/** 
	 * \brief this function implements the behaviour if a transition from failsafe to mixing is taking place
	 */
	static void transitionToMixingFunc();
	
private:

	/** 
	 * \brief No public constructing
	 */
	ControlOmnidrive3Wheels() { }
	
	static uint16_t const DEADZONE_US = 50;
		
	/** 
	 * \brief returns true if 1500 - deadzone_us <= pulse_duration_us <= 1500 + deadzone_us
	 */
	static bool isStickInCenterPosition(uint16_t const pulse_duration_us, uint16_t const deadzone_us);
	
	/** 
	 * \brief this function controls the moving of the omnidirectional platform
	 */
	static void doMove(uint16_t const fwd_bwd, uint16_t const left_right);

	/** 
	 * \brief this function controls the rotation of the omnidirectional platform
	 */	
	static void doRotate(uint16_t const rotate);
	
	/** 
	 * \brief absolutely do nothing - all outputs are at 1500 (neutral value)
	 */	
	static void doNothing();
	
	/** 
	 * \brief control the three motors
	 */
	static void setMotorA(uint16_t const pulse_duration_us);
	static void setMotorB(uint16_t const pulse_duration_us);
	static void setMotorC(uint16_t const pulse_duration_us);
};

#endif

#endif /* OMNIDRIVE_3_WHEELS_H_ */