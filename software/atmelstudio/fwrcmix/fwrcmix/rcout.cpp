/**
 * \file rcout.cpp
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief control up to 6 PWM outputs for generating rc pwm signals (20 ms period, pulse duration between 1 and 2 ms)
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "rcout.h"

#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "hal.h"

/************************************************************************/
/* PRIVATE TYPEDEFS													    */
/************************************************************************/

/* Defines a function pointer which is called to initialize a output */

typedef void(*initRcOutFunc)(void);

/* Defines two function pointers which can be used so set (to HIGH) or
 * clear (to LOW) an RcOut pwm output
 */

typedef void(*setRcOutFunc)(void);
typedef void(*clearRcOutFunc)(void);

/* This structure contains the complete information which is required to
 * control an rc output via this module 
 */

typedef struct  
{
	/* Input fields to configure the state by the users of this module
	 * via the provided interface functions 
	 */
	
	E_RC_OUT_STATE state;			/* The current state of the rc output, whether it is turned on or off */
	uint16_t pulse_duration_us;		/* The pulse duration of the rc output pulse (duration of the output pin being 'high') */
	
	/* I/O functions for accessing the concrete GPIO output pin */
	
	initRcOutFunc initRcOut;		/* This function pointer points to a function which initializes the gpio output functionality of a rc output */
	setRcOutFunc setRcOut;			/* This function pointer points to the function which sets the rc output to 'high' */
	clearRcOutFunc clearRcOut;		/* This function pointer points to the function which clear the rc output to 'low' */

} T_RC_OUT_DATA;

/************************************************************************/
/* PRIVATE CONTANTS													    */
/************************************************************************/

static uint8_t const NUM_RC_OUT_CHANNELS = 6;

/* fClk = 16 MHz
 * fTimer = 2 MHz -> tTimer = 0.5 us -> Prescaler = 8
 * TTimer = 20 ms -> Steps per TTimer = 20 ms / 0.5 us = 40000
 * TimerReloadValue = 0xFFFF (65535) - 40000 = 0x63BF (25535)
 */

static uint16_t const TIMER_RELOAD_VALUE = 0x63BF;

/************************************************************************/
/* PRIVATE DATA														    */
/************************************************************************/

static volatile T_RC_OUT_DATA RcOutData[NUM_RC_OUT_CHANNELS] =
{
	{ OUTx_OFF, 1500, initOut1, setOut1, clearOut1 },	/* OUT1 */
	{ OUTx_OFF, 1500, initOut2, setOut2, clearOut2 },	/* OUT2 */
	{ OUTx_OFF, 1500, initOut3, setOut3, clearOut3 },	/* OUT3 */
	{ OUTx_OFF, 1500, initOut4, setOut4, clearOut4 },	/* OUT4 */
	{ OUTx_OFF, 1500, initOut5, setOut5, clearOut5 },	/* OUT5 */
	{ OUTx_OFF, 1500, initOut6, setOut6, clearOut6 }	/* OUT6 */
};

static volatile bool OutputCompareMatchAclearOut1 = true;
static volatile bool OutputCompareMatchBclearOut2 = true;
static volatile bool OutputCompareMatchCclearOut3 = true;

/************************************************************************/
/* PRIVATE FUNCTIONS                                                    */
/************************************************************************/

/** 
 * \brief set an rc output if the state is on, clear it otherwise
 */
void setRcOutIfStateIsOn(E_RC_OUT_SELECT const sel)
{
	if(RcOutData[sel].state == OUTx_ON)
	{
		RcOutData[sel].setRcOut();
	}
	else
	{
		RcOutData[sel].clearRcOut();
	}	
}

/** 
 * \brief clear an rc output
 */
void clearRcOut(E_RC_OUT_SELECT const sel)
{
	RcOutData[sel].clearRcOut();
}

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief initialize the RcOut class (setup the timers, etc.)
 */
void RcOut::begin()
{
	/* Initialize all Outputs and set them to low*/
	
	for(uint8_t i = 0; i < NUM_RC_OUT_CHANNELS; i++)
	{
		RcOutData[i].initRcOut();
		RcOutData[i].clearRcOut();
	}	
	
	/* Operate in normal timer mode, Top = 0xFFFF */
	
	TCCR1A = 0;
	
	/* Ensure that TCCR1C is set to reset value (Arduino IDE might
	 * corrupt this registers at a future point in time because
	 * it needs the registers for its own purposes
	 */
	
	TCCR1C = 0;
	
	/* Set the Timer/Counter register of Timer 1 to the precalculated
	 * reload value.
	 */
	
	TCNT1 = TIMER_RELOAD_VALUE;
	
	/* Enable all 3 output compare interrupts as well as the timer
	 * overflow interrupt 
	 */
	
	TIMSK1 = (1<<OCIE1C) | (1<<OCIE1B) | (1<<OCIE1A) | (1<<TOIE1);
	
	/* Set prescaler to 8 - now the timer is active */
		
	TCCR1B = (1<<CS11);
}

/** 
 * \brief turn an output either on or off - off outputs have constant LOW level (0 V)
 */
void RcOut::setRcOutState(E_RC_OUT_SELECT const sel, E_RC_OUT_STATE const state)
{
	RcOutData[sel].state = state;
}
	
/** 
 * \brief set the pulse duration of a desired rc mixer output
 */
void RcOut::setPwmPulseDurationUs(E_RC_OUT_SELECT const sel, uint16_t const pulse_duration_us)
{
	RcOutData[sel].pulse_duration_us = pulse_duration_us;
}

/************************************************************************/
/* INTERRUPT SERVICE HANDLERS                                           */
/************************************************************************/

/** 
 * \brief Interrupt Service Routine for Timer 1 - this function is 
 * executed every 20 ms
 */
ISR(TIMER1_OVF_vect)
{
	/* Reload the Timer/Counter register with the correct reload value */
	
	TCNT1 = TIMER_RELOAD_VALUE;
	
	/* We have 6 PWM outputs but only 2 output compare registers -
	 * how do we generate then 6 PWM signals? Solution is quite 
	 * simple:
	 * - OUT1-3 signals are set in the timer 0 overflow isr every 20 ms
	 * - Output compare registers A-C are preloaded with a value which represents
	 *   the pwm pulse duration
	 * - OUT1-3 signals are cleared in the output compare match 
	 *   interrupt service routine
	 * - In the output compare match interrupt service routines set the
	 *   output compare match registers to trigger pulse_duration_us
	 *   of the individual output channel OUT4 to OUT6 before the 
	 *   timer overflow interrupt service occurs.
	 * - In the second iteration of output compare match interrupts
	 *   set the Outputs OUT4 to OUT6. Those are cleared upon occurence
	 *   of the timer overflow interrupt.
	 * - go back to first entry in this list ;)
	 */
	
	/* Set OUT1 to OUT3 */
	
	setRcOutIfStateIsOn(OUT1);
	setRcOutIfStateIsOn(OUT2);
	setRcOutIfStateIsOn(OUT3);
	
	/* Clear OUT4 to OUT6 */
	
	clearRcOut(OUT4);
	clearRcOut(OUT5);
	clearRcOut(OUT6);
	
	/* Setup output compare registers to be triggered when outputs
	 * OUT1 to OUT3 need to be turned off. Attention: We need to
	 * multiply the value provided in the variable pulse_duration_us
	 * by a factor of 2 since a single timer step is only 0.5 us
	 * long.
	 */
	
	OCR1A = TIMER_RELOAD_VALUE + RcOutData[OUT1].pulse_duration_us * 2;	
	OCR1B = TIMER_RELOAD_VALUE + RcOutData[OUT2].pulse_duration_us * 2;	
	OCR1C = TIMER_RELOAD_VALUE + RcOutData[OUT3].pulse_duration_us * 2;	
	
	/* Setup the status flags so we know that we need to clear
	 * OUT1 to OUT3 in the output compare match interrupts
	 */
	
	OutputCompareMatchAclearOut1 = true;
	OutputCompareMatchBclearOut2 = true;
	OutputCompareMatchCclearOut3 = true;
}

/** 
 * \brief Interrupt service routine for compare match a interrupt
 */
ISR(TIMER1_COMPA_vect)
{
	if(OutputCompareMatchAclearOut1)
	{
		/* Clear OUT1 */
		
		clearRcOut(OUT1);
		
		OutputCompareMatchAclearOut1 = false;
		
		/* Setup output compare register to be triggered pulse_duration_us
		 * before the timer overflow interrupt. Attention: We also need to
		 * multiply the value provided in pulse_duration_us by 2 to take 
		 * account for a timer step duration of 0.5 us.
		 */
	
		OCR1A = 0xFFFF - RcOutData[OUT4].pulse_duration_us * 2;
	}
	else
	{
		/* Set OUT4 */
	
		setRcOutIfStateIsOn(OUT4);
	}
}

/* Output compare match interrupt service routines B and C follow
 * the pattern established with A. Therefor I won't them document
 * them so carefully as A. You should by now have an idea how this
 * works ;)
 */

/** 
 * \brief Interrupt service routine for compare match b interrupt
 */
ISR(TIMER1_COMPB_vect)
{
	if(OutputCompareMatchBclearOut2)
	{
		/* Clear OUT2 */
	
		clearRcOut(OUT2);
		
		OutputCompareMatchBclearOut2 = false;
	
		/* Setup output compare register */
		
		OCR1B = 0xFFFF - RcOutData[OUT5].pulse_duration_us * 2;		
	}
	else
	{
		/* Set OUT5 */
	
		setRcOutIfStateIsOn(OUT5);
	}
}

/** 
 * \brief Interrupt service routine for compare match c interrupt
 */
ISR(TIMER1_COMPC_vect)
{
	if(OutputCompareMatchCclearOut3)
	{
		/* Clear OUT3 */
	
		clearRcOut(OUT3);
	
		OutputCompareMatchCclearOut3 = false;	
	
		/* Setup output compare register */
		
		OCR1C = 0xFFFF - RcOutData[OUT6].pulse_duration_us * 2;
	}
	else
	{
		/* Set OUT6 */
		
		setRcOutIfStateIsOn(OUT6);
	}	
}