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

#ifndef OMNIDRIVE_3_WHEELS_H_
#define OMNIDRIVE_3_WHEELS_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#ifdef CONFIG_USE_CONTROL_OMNIDRIVE_3_WHEELS

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class ControlOmnidrive3Wheels
{

public:

  /**
   * \brief this function returns true when all signals used in this specific mixer are good
   */
  static bool isGoodFunc();

  /**
   * \brief this function implements the failsafe behavior of this specific mixer
   */
  static void failsafeFunc();

  /**
   * \brief this function implements the mixing behavior (function fOUT(IN1, IN2, ...) of this specific mixer
   */
  static void mixingFunc();

  /**
   * \brief this function implements the behaviour if a transition from mixing to failsafe is taking place
   */
  static void transitionToFailsafeFunc();

  /**
   * \brief this function implements the behaviour if a transition from failsafe to mixing is taking place
   */
  static void transitionToMixingFunc();

private:

  /**
   * \brief No public constructing
   */
  ControlOmnidrive3Wheels()
  {
  }

  static uint16_t const DEADZONE_US = 50;

  /**
   * \brief returns true if 1500 - deadzone_us <= pulse_duration_us <= 1500 + deadzone_us
   */
  static bool isStickInCenterPosition(uint16_t const pulse_duration_us, uint16_t const deadzone_us);

  /**
   * \brief this function controls the moving of the omnidirectional platform
   */
  static void doMove(uint16_t const fwd_bwd, uint16_t const left_right);

  /**
   * \brief this function controls the rotation of the omnidirectional platform
   */
  static void doRotate(uint16_t const rotate);

  /**
   * \brief absolutely do nothing - all outputs are at 1500 (neutral value)
   */
  static void doNothing();

  /**
   * \brief control the three motors
   */
  static void setMotorA(uint16_t const pulse_duration_us);
  static void setMotorB(uint16_t const pulse_duration_us);
  static void setMotorC(uint16_t const pulse_duration_us);
};

#endif

#endif /* OMNIDRIVE_3_WHEELS_H_ */
