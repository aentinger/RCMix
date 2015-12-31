/**
 * \file hal.h
 * \author Alexander Entinger, MSc
 * \copyright LXRobotics GmbH
 * \brief hardware abstraction layer
 * \license 
 */

#ifndef HAL_H_
#define HAL_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <avr/io.h>

/************************************************************************/
/* DEFINES                                                              */
/************************************************************************/

/* OUT1 = PD7 */

#define OUT1_DDR		(DDRD)
#define OUT1_PORT		(PORTD)
#define OUT1_bm			(1<<7)

/* OUT2 = PB4 */

#define OUT2_DDR		(DDRB)
#define OUT2_PORT		(PORTB)
#define OUT2_bm			(1<<4)

/* OUT3 = PB5 */

#define OUT3_DDR		(DDRB)
#define OUT3_PORT		(PORTB)
#define OUT3_bm			(1<<5)

/* OUT4 = PB6 */

#define OUT4_DDR		(DDRB)
#define OUT4_PORT		(PORTB)
#define OUT4_bm			(1<<6)

/* OUT5 = PC6 */

#define OUT5_DDR		(DDRC)
#define OUT5_PORT		(PORTC)
#define OUT5_bm			(1<<6)

/* OUT6 = PC7 */

#define OUT6_DDR		(DDRC)
#define OUT6_PORT		(PORTC)
#define OUT6_bm			(1<<7)

/************************************************************************/
/* PUBLIC FUNCTIONS                                                     */
/************************************************************************/

static void initOut1() { OUT1_DDR |= OUT1_bm; }
static void setOut1() { OUT1_PORT |= OUT1_bm; }
static void clearOut1() { OUT1_PORT &= ~OUT1_bm; }
	
static void initOut2() { OUT2_DDR |= OUT2_bm; }
static void setOut2() { OUT2_PORT |= OUT2_bm; }
static void clearOut2() { OUT2_PORT &= ~OUT2_bm; }

static void initOut3() { OUT3_DDR |= OUT3_bm; }
static void setOut3() { OUT3_PORT |= OUT3_bm; }
static void clearOut3() { OUT3_PORT &= ~OUT3_bm; }
	
static void initOut4() { OUT4_DDR |= OUT4_bm; }
static void setOut4() { OUT4_PORT |= OUT4_bm; }
static void clearOut4() { OUT4_PORT &= ~OUT4_bm; }
	
static void initOut5() { OUT5_DDR |= OUT5_bm; }
static void setOut5() { OUT5_PORT |= OUT5_bm; }
static void clearOut5() { OUT5_PORT &= ~OUT5_bm; }
	
static void initOut6() { OUT6_DDR |= OUT6_bm; }
static void setOut6() { OUT6_PORT |= OUT6_bm; }
static void clearOut6() { OUT6_PORT &= ~OUT6_bm; }

#endif /* HAL_H_ */