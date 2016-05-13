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

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "led.h"
#include "rcin.h"
#include "rcout.h"
#include "control.h"

#include "config.h"

#if defined(CONFIG_USE_CONTROL_DEMO)
#include "control_demo.h"
#elif defined(CONFIG_USE_CONTROL_OMNIDRIVE_3_WHEELS)
#include "control_omnidrive_3_wheels.h"
#endif

/************************************************************************/
/* GLOBAL VARIABLES                                                     */
/************************************************************************/

Control control(
#if defined(CONFIG_USE_CONTROL_DEMO)
  &ControlDemo::isGoodFunc, 
  &ControlDemo::failsafeFunc, 
  &ControlDemo::mixingFunc, 
  &ControlDemo::transitionToFailsafeFunc, 
  &ControlDemo::transitionToMixingFunc
#elif defined(CONFIG_USE_CONTROL_OMNIDRIVE_3_WHEELS)
  ControlOmnidrive3Wheels::isGoodFunc, 
  ControlOmnidrive3Wheels::failsafeFunc, 
  ControlOmnidrive3Wheels::mixingFunc, 
  ControlOmnidrive3Wheels::transitionToFailsafeFunc, 
  ControlOmnidrive3Wheels::transitionToMixingFunc
#endif
  );

/************************************************************************/
/* ARDUINO FUNCTIONS                                                    */
/************************************************************************/

void setup()
{
  Led::begin();
  RcIn::begin();
  RcOut::begin();
}

void loop()
{
  control.execute();
}

/************************************************************************/
/* INTERRUPTS                                                           */
/************************************************************************/

/** 
 * \brief this interrupt is executed when a interrupt is triggered
 * for which no isr was installed - signal a failure in that case.
 */
ISR(BADISR_vect)
{
	for(;;)
	{
		_delay_ms(50);
		Led::setState(LED_ON);
		_delay_ms(50);
		Led::setState(LED_OFF);
	}
}
