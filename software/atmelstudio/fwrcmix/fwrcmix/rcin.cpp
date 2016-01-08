/**
 * \file rcin.cpp
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief Interpret and decode up to 4 PWM input signals
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "rcin.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "hal.h"

/************************************************************************/
/* PRIVATE TYPEDEFS													    */
/************************************************************************/

/* Defines a function pointer which is called to initialize a input */

typedef void(*initRcInFunc)(void);

/* Define two functions which can be used to setup whether an interrupt is
 * generated for a rising or a falling edge event
 */

typedef void(*triggerAtRisingEdgeFunc)(void);
typedef void(*triggerAtFallingEdgeFunc)(void);

typedef enum {RISING, FALLING} E_PULSE_STATE;

/* The structure contains all the information for handling an rc input */

typedef struct  
{
	/* Output fields for communicating information to the users of
	 * this module 
	 */
	
	bool is_good;
	uint16_t pulse_duration_us;
	
	/* Management fields for this module required to interpret the 
	 * incoming signals and setting up the module.
	 */

	E_PULSE_STATE pulse_state;		/* Determines wether we expect a rising or a falling edge */
	uint8_t pulses_received;		/* The number of pulses received in one full timer cycle */
	uint16_t timer_start;			/* Value of the timer when a pwm pulse starts (rising edge) */
	uint16_t timer_stop;			/* Value of the timer when a pwm pulse stops (falling edge) */
	
	/* I/O functions for accessing the concrete GPIO input pin */
	
	initRcInFunc initRcIn;							/* This function pointer points to a function which initializes gpio input pin */
	triggerAtRisingEdgeFunc triggerAtRisingEdge;	/* Set the external interrupt up to be triggered at a rising edge */
	triggerAtFallingEdgeFunc triggerAtFallingEdge;	/* Set the external interrupt up to be triggered at a falling edge */

} T_RC_IN_DATA;

/************************************************************************/
/* PRIVATE CONTANTS													    */
/************************************************************************/

static uint8_t const NUM_RC_IN_CHANNELS = 4;

static uint8_t const MIN_PULSES_PER_TIMER_CYCLE = 10; // 262 ms / 20 ms = 13 (-3 to give a little room for error)static uint16_t const MIN_PULSE_WIDTH_US = 1000;static uint16_t const MAX_PULSE_WIDTH_US = 2000;

/************************************************************************/
/* PRIVATE DATA														    */
/************************************************************************/

static volatile T_RC_IN_DATA RcInData[NUM_RC_IN_CHANNELS] =
{
	{ false, 0, RISING, 0, 0, 0, initIn1, triggerIn1AtRisingEdge, triggerIn1AtFallingEdge },	/* IN1 */
	{ false, 0, RISING, 0, 0, 0, initIn2, triggerIn2AtRisingEdge, triggerIn2AtFallingEdge },	/* IN2 */
	{ false, 0, RISING, 0, 0, 0, initIn3, triggerIn3AtRisingEdge, triggerIn3AtFallingEdge },	/* IN3 */
	{ false, 0, RISING, 0, 0, 0, initIn4, triggerIn4AtRisingEdge, triggerIn4AtFallingEdge }		/* IN4 */
};

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief initialize thc RcIn module
 */
void RcIn::begin()
{
	/* Initialize all inputs and set them up to trigger at rising edge */
		
	for(uint8_t i = 0; i < NUM_RC_IN_CHANNELS; i++)
	{
		RcInData[i].initRcIn();
		
		RcInData[i].triggerAtRisingEdge();
		RcInData[i].pulse_state = RISING;
	}
	
	/* Operate in normal timer mode, Top = 0xFFFF */
	
	TCCR3A = 0;
	
	/* Ensure that TCCR3C is set to reset value (Arduino IDE might
	 * corrupt this registers at a future point in time because
	 * it needs the registers for its own purposes
	 */
	
	TCCR3C = 0;
	
	/* Ensure that TCNT3 is zero for the start */
	
	TCNT3 = 0;
	
	/* Enable Timer 3 overflow interrupt */
	
	TIMSK3 = (1<<TOIE3);
	
	/* Start the timer with a prescaler of 64
	 * fTimer = fCPU / 64 = 16 MHz / 64 = 250 kHz
	 * tTimerStep = 4 us
	 * 2^16 * tTimerStep = 262.144 ms (1 full timer cycle)
	 */
	
	TCCR3B = (1<<CS31) | (1<<CS30);	
	
	/* Enable all four external interrupts */
	
	EIMSK = (1<<INT3) | (1<<INT2) | (1<< INT1) | (1<<INT0);
}
	
/** 
 * \brief returns true if the selected input channel has received valid signals
 */
bool RcIn::isGood(E_RC_IN_SELECT const sel)
{
	return RcInData[sel].is_good;
}
	
/** 
 * \brief returns the duration of the pulses on the selected input channel
 */
uint16_t RcIn::getPulseDurationUs(E_RC_IN_SELECT const sel)
{
	return RcInData[sel].pulse_duration_us;
}

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief this function is called from the timer 3 overflow interrupt
 * service routine for every input and checks whether we still have
 * good signals (or not) and updates the is_good flag accordingly.
 */
void RcInXTimerOverflowISR(E_RC_IN_SELECT const sel)
{
	/* Check if we have received as many pulses from the rc transceiver	 * as we expect. Otherwise we might be in a failsafe situation 	 */		bool const pulses_lost = RcInData[sel].pulses_received < MIN_PULSES_PER_TIMER_CYCLE;	if(pulses_lost)	{		/* Reinitialize the input, we are now waiting for the next		 * rising edge to come which would indicate the start of a		 * new pwm pulse		 */					RcInData[sel].pulse_state = RISING;		RcInData[sel].triggerAtRisingEdge();		RcInData[sel].is_good = false;	}	else	{		RcInData[sel].is_good = true;	}	/* Reset the pulse counter */		RcInData[sel].pulses_received = 0;
}

/** 
 * \brief this function is called from the various external interrupt handlers
 * and is used to calculate the pulse duration of a pwm pulse.
 */
void RcInXIntXISR(E_RC_IN_SELECT const sel)
{
	if(RcInData[sel].pulse_state == RISING)	{		RcInData[sel].timer_start = TCNT3;		RcInData[sel].pulse_state = FALLING;		RcInData[sel].triggerAtFallingEdge();	}	else if(RcInData[sel].pulse_state == FALLING)	{		RcInData[sel].timer_stop = TCNT3;		RcInData[sel].pulse_state = RISING;		RcInData[sel].triggerAtRisingEdge();				/* Calculate the duration of the pulse */					uint16_t const pulse_duration_in_timer_steps = RcInData[sel].timer_stop - RcInData[sel].timer_start;		uint16_t const timerstep_duration_in_us = 4;		uint16_t const pulse_duration_in_us = pulse_duration_in_timer_steps * timerstep_duration_in_us;					/* Only update when the value is within acceptable bounds */				if(pulse_duration_in_us >= MIN_PULSE_WIDTH_US && pulse_duration_in_us <= MAX_PULSE_WIDTH_US)		{			RcInData[sel].pulse_duration_us = pulse_duration_in_us;							RcInData[sel].pulses_received++;		}	}
}

/************************************************************************/
/* INTERRUPT SERVICE HANDLERS                                           */
/************************************************************************/

/**  * \brief timer 3 overflow interrupt service routine */ISR(TIMER3_OVF_vect) {	RcInXTimerOverflowISR(IN1);	RcInXTimerOverflowISR(IN2);	RcInXTimerOverflowISR(IN3);	RcInXTimerOverflowISR(IN4);}/**  * \brief INT0 (PD0 = IN4) interrupt service routine */ISR(INT0_vect){	RcInXIntXISR(IN4);}/**  * \brief INT1 (PD1 = IN3) interrupt service routine */ISR(INT1_vect){	RcInXIntXISR(IN3);}/**  * \brief INT2 (PD2 = IN2) interrupt service routine */ISR(INT2_vect){	RcInXIntXISR(IN2);}/**  * \brief INT3 (PD3 = IN1) interrupt service routine */ISR(INT3_vect){	RcInXIntXISR(IN1);}