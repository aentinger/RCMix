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

#ifndef RCIN_H_
#define RCIN_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef enum
{
  IN1 = 0, IN2 = 1, IN3 = 2, IN4 = 3
} E_RC_IN_SELECT;

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class RcIn
{

public:

  /**
   * \brief initialize thc RcIn module
   */
  static void begin();

  /**
   * \brief returns true if the selected input channel has received valid signals
   */
  static bool isGood(E_RC_IN_SELECT const sel);

  /**
   * \brief returns the duration of the pulses on the selected input channel
   */
  static uint16_t getPulseDurationUs(E_RC_IN_SELECT const sel);

private:

  /**
   * \brief no public constructing
   */
  RcIn() { }
};

#endif /* RCIN_H_ */
