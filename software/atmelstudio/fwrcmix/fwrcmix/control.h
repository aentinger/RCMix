/**
 * \file control.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief This class implements switching between failsafe and mixing mode as well as calling 
 * the concrete failsafe and mixing functions of your control implementation
 * \license 
 */


#ifndef CONTROL_H_
#define CONTROL_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdbool.h>

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef bool(*controlIsGoodFunc)(void);					/* This function is used to determine wether we are in failsafe or in mixing mode */
typedef void(*controlFailsafeFunc)(void);				/* This function is executed upon occurence of an failsafe event */
typedef void(*controlMixingFunc)(void);					/* This function is executed in normal mixing mode */
typedef void(*controlOnTransitionToFailsafe)(void);		/* This function is called on the transition from mixing to failsafe mode */
typedef void(*controlOnTransitionToMixing)(void);		/* This function is called on the transition from failsafe to mixing mode */

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class Control
{

public:

	/** 
	 * \brief The Constructor is handed over function pointers which point to the 
	 * concrete implementation of the desired mixing functionality.
	 */ 
	Control(controlIsGoodFunc isGoodFunc, controlFailsafeFunc failsafeFunc, controlMixingFunc mixingFunc, controlOnTransitionToFailsafe transitionToFailsafeFunc, controlOnTransitionToMixing transitionToMixingFunc);
	
	/** 
	 * \brief This function is executed in the main loop. Here we call the 
	 * concrete failsafe and mixing functions and accomplish the state 
	 * transition between those states.
	 */
	void execute();
	
private:

	enum { FAILSAFE, MIXING } _state;

	controlIsGoodFunc _isGoodFunc;
	controlFailsafeFunc _failsafeFunc;
	controlMixingFunc _mixingFunc;
	controlOnTransitionToFailsafe _transitionToFailsafeFunc;
	controlOnTransitionToMixing _transitionToMixingFunc;

	bool isGood();
	void toogleLed();
	void turnLedOn();
};

#endif /* CONTROL_H_ */