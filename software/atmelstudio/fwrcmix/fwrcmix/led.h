/**
 * \file led.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief class for controlling the used led
 * \license 
 */

#ifndef LED_H_
#define LED_H_

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef enum
{
	LED_ON, LED_OFF
} E_LED_STATE;

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class Led
{
public:

	/** 
	 * \brief initialize the led module
	 */
	static void begin();
	
	/** 
	 * \brief turn the led on or off
	 */
	static void setState(E_LED_STATE const state);
	
private:
	/** 
	 * \brief no public constructing
	 */	
	Led() { }
};

#endif /* LED_H_ */