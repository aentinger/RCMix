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

#ifndef RCOUT_H_
#define RCOUT_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef enum
{
  OUT1 = 0, OUT2 = 1, OUT3 = 2, OUT4 = 3, OUT5 = 4, OUT6 = 5
} E_RC_OUT_SELECT;

typedef enum
{
  OUTx_ON, OUTx_OFF
} E_RC_OUT_STATE;

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class RcOut
{

public:

  /**
   * \brief initialize the RcOut class (setup the timers, etc.)
   */
  static void begin();

  /**
   * \brief turn an output either on or off - off outputs have constant LOW level (0 V)
   */
  static void setRcOutState(E_RC_OUT_SELECT const sel, E_RC_OUT_STATE const state);

  /**
   * \brief set the pulse duration of a desired rc mixer output
   */
  static void setPwmPulseDurationUs(E_RC_OUT_SELECT const sel, uint16_t const pulse_duration_us);

private:

  /**
   * \brief no public constructing
   */
  RcOut() { }

};

#endif /* RCOUT_H_ */
