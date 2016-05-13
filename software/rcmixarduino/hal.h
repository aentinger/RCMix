/*
 * MIT License
 *
 * Copyright (c) 2016 LXRobotics GmbH / Alexander Entinger, MSc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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

/* ULED = PB7 */

#define ULED_DDR		(DDRB)
#define ULED_PORT		(PORTB)
#define ULED_bm			(1<<7)

/* IN1 = PD3 = INT3 */

#define IN1_DDR				      (DDRD)
#define IN1_PORT			      (PORTD)
#define IN1_bm				      (1<<3)
#define EINT_IN1_rising_bm	((1<<ISC31) | (1<<ISC30))
#define EINT_IN1_falling_bm	(1<<ISC31)
#define EINT_IN1_clear_bm	  (~EINT_IN1_rising_bm)

/* IN2 = PD2 = INT2 */

#define IN2_DDR				      (DDRD)
#define IN2_PORT			      (PORTD)
#define IN2_bm				      (1<<2)
#define EINT_IN2_rising_bm	((1<<ISC21) | (1<<ISC20))
#define EINT_IN2_falling_bm	(1<<ISC21)
#define EINT_IN2_clear_bm	  (~EINT_IN2_rising_bm)

/* IN3 = PD1 = INT1 */

#define IN3_DDR				(DDRD)
#define IN3_PORT			(PORTD)
#define IN3_bm				(1<<1)
#define EINT_IN3_rising_bm	((1<<ISC11) | (1<<ISC10))
#define EINT_IN3_falling_bm	(1<<ISC11)
#define EINT_IN3_clear_bm	(~EINT_IN3_rising_bm)

/* IN4 = PD0 = INT0 */

#define IN4_DDR				      (DDRD)
#define IN4_PORT			      (PORTD)
#define IN4_bm				      (1<<0)
#define EINT_IN4_rising_bm	((1<<ISC01) | (1<<ISC00))
#define EINT_IN4_falling_bm	(1<<ISC01)
#define EINT_IN4_clear_bm	  (~EINT_IN4_rising_bm)

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

void initOut1();
void setOut1();
void clearOut1();

void initOut2();
void setOut2();
void clearOut2();

void initOut3();
void setOut3();
void clearOut3();

void initOut4();
void setOut4();
void clearOut4();

void initOut5();
void setOut5();
void clearOut5();

void initOut6();
void setOut6();
void clearOut6();

void initULed();
void setULed();
void clearULed();

void initIn1();
void triggerIn1AtRisingEdge();
void triggerIn1AtFallingEdge();

void initIn2();
void triggerIn2AtRisingEdge();
void triggerIn2AtFallingEdge();

void initIn3();
void triggerIn3AtRisingEdge();
void triggerIn3AtFallingEdge();

void initIn4();
void triggerIn4AtRisingEdge();
void triggerIn4AtFallingEdge();

#endif /* HAL_H_ */
