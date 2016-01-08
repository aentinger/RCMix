/**
 * \file hal.cpp
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief hardware abstraction layer
 * \license 
 */

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include "hal.h"

/************************************************************************/
/* PUBLIC FUNCTIONS                                                     */
/************************************************************************/

void initOut1() { OUT1_DDR |= OUT1_bm; }
void setOut1() { OUT1_PORT |= OUT1_bm; }
void clearOut1() { OUT1_PORT &= ~OUT1_bm; }

void initOut2() { OUT2_DDR |= OUT2_bm; }
void setOut2() { OUT2_PORT |= OUT2_bm; }
void clearOut2() { OUT2_PORT &= ~OUT2_bm; }

void initOut3() { OUT3_DDR |= OUT3_bm; }
void setOut3() { OUT3_PORT |= OUT3_bm; }
void clearOut3() { OUT3_PORT &= ~OUT3_bm; }

void initOut4() { OUT4_DDR |= OUT4_bm; }
void setOut4() { OUT4_PORT |= OUT4_bm; }
void clearOut4() { OUT4_PORT &= ~OUT4_bm; }

void initOut5() { OUT5_DDR |= OUT5_bm; }
void setOut5() { OUT5_PORT |= OUT5_bm; }
void clearOut5() { OUT5_PORT &= ~OUT5_bm; }

void initOut6() { OUT6_DDR |= OUT6_bm; }
void setOut6() { OUT6_PORT |= OUT6_bm; }
void clearOut6() { OUT6_PORT &= ~OUT6_bm; }
	
void initULed() { ULED_DDR |= ULED_bm; }
void setULed() { ULED_PORT |= ULED_bm; }
void clearULed() { ULED_PORT &= ~ULED_bm; }

void initIn1() { IN1_DDR &= ~IN1_bm; IN1_PORT |= IN1_bm; }
void triggerIn1AtRisingEdge() { EICRA &= EINT_IN1_clear_bm; EICRA |= EINT_IN1_rising_bm; }
void triggerIn1AtFallingEdge() { EICRA &= EINT_IN1_clear_bm; EICRA |= EINT_IN1_falling_bm; }
	
void initIn2() { IN2_DDR &= ~IN2_bm; IN2_PORT |= IN2_bm; }
void triggerIn2AtRisingEdge() { EICRA &= EINT_IN2_clear_bm; EICRA |= EINT_IN2_rising_bm; }
void triggerIn2AtFallingEdge() { EICRA &= EINT_IN2_clear_bm; EICRA |= EINT_IN2_falling_bm; }
	
void initIn3() { IN3_DDR &= ~IN3_bm; IN3_PORT |= IN3_bm; }
void triggerIn3AtRisingEdge() { EICRA &= EINT_IN3_clear_bm; EICRA |= EINT_IN3_rising_bm; }
void triggerIn3AtFallingEdge() { EICRA &= EINT_IN3_clear_bm; EICRA |= EINT_IN3_falling_bm; }
	
void initIn4() { IN4_DDR &= ~IN4_bm; IN4_PORT |= IN4_bm; }
void triggerIn4AtRisingEdge() { EICRA &= EINT_IN4_clear_bm; EICRA |= EINT_IN4_rising_bm; }
void triggerIn4AtFallingEdge() { EICRA &= EINT_IN4_clear_bm; EICRA |= EINT_IN4_falling_bm; }