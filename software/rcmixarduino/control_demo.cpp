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

#include "control_demo.h"

#include <stdbool.h>

#include "rcin.h"
#include "rcout.h"

#ifdef CONFIG_USE_CONTROL_DEMO

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief this function returns true when all signals used in this specific mixer are good
 */
bool ControlDemo::isGoodFunc()
{
  return (RcIn::isGood(IN1) && RcIn::isGood(IN2) && RcIn::isGood(IN3) && RcIn::isGood(IN4));
}

/** 
 * \brief this function implements the failsafe behaviour of this specific mixer
 */
void ControlDemo::failsafeFunc()
{
  /* Nothing to do here, outputs are turned off in the
   * transition to failsafe
   */
}

/** 
 * \brief this function implements the mixing behavior (function fOUT(IN1, IN2, ...) of this specific mixer
 */
void ControlDemo::mixingFunc()
{
  RcOut::setPwmPulseDurationUs(OUT1, RcIn::getPulseDurationUs(IN1));
  RcOut::setPwmPulseDurationUs(OUT2, RcIn::getPulseDurationUs(IN2));
  RcOut::setPwmPulseDurationUs(OUT3, RcIn::getPulseDurationUs(IN3));
  RcOut::setPwmPulseDurationUs(OUT4, RcIn::getPulseDurationUs(IN4));
}

/** 
 * \brief this function implements the behaviour if a transition from mixing to failsafe is taking place
 */
void ControlDemo::transitionToFailsafeFunc()
{
  RcOut::setRcOutState(OUT1, OUTx_OFF);
  RcOut::setRcOutState(OUT2, OUTx_OFF);
  RcOut::setRcOutState(OUT3, OUTx_OFF);
  RcOut::setRcOutState(OUT4, OUTx_OFF);
}

/** 
 * \brief this function implements the behaviour if a transition from failsafe to mixing is taking place
 */
void ControlDemo::transitionToMixingFunc()
{
  RcOut::setRcOutState(OUT1, OUTx_ON);
  RcOut::setRcOutState(OUT2, OUTx_ON);
  RcOut::setRcOutState(OUT3, OUTx_ON);
  RcOut::setRcOutState(OUT4, OUTx_ON);
}

#endif
