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

#include "control_omnidrive_3_wheels.h"

#include <math.h>

#include "rcin.h"
#include "rcout.h"

#ifdef CONFIG_USE_CONTROL_OMNIDRIVE_3_WHEELS

/************************************************************************/
/* CONSTANTS                                                            */
/************************************************************************/

static uint16_t const CENTER_VALUE_PULSE_WIDTH_US = 1500;

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief this function returns true when all signals used in this specific mixer are good
 */
bool ControlOmnidrive3Wheels::isGoodFunc()
{
  return (RcIn::isGood(IN1) && RcIn::isGood(IN2) && RcIn::isGood(IN3));
}

/** 
 * \brief this function implements the failsafe behaviour of this specific mixer
 */
void ControlOmnidrive3Wheels::failsafeFunc()
{
  /* Nothing to do here, outputs are turned off in the
   * transition to failsafe
   */
}

/** 
 * \brief this function implements the mixing behavior (function fOUT(IN1, IN2, ...) of this specific mixer
 */
void ControlOmnidrive3Wheels::mixingFunc()
{
  /* IN1
   *  IN1 > 1500 -> FWD
   *  IN1 < 1500 -> BWD
   * IN2
   *  IN2 > 1500 -> RIGHT
   *  IN2 < 1500 -> LEFT
   * IN3
   *  IN3 > 1500 -> ROTATE CLOCKWISE
   *  IN3 < 1500 -> ROTATE COUNTER CLOCKWISE
   */

  uint16_t const fwd_bwd = RcIn::getPulseDurationUs(IN1);
  uint16_t const left_right = RcIn::getPulseDurationUs(IN2);
  uint16_t const rotate = RcIn::getPulseDurationUs(IN3);

  bool const do_move = !isStickInCenterPosition(fwd_bwd, DEADZONE_US)
      || !isStickInCenterPosition(left_right, DEADZONE_US);
  bool const do_rotate = !isStickInCenterPosition(rotate, DEADZONE_US);

  /* OUT1 = MOTOR A
   * OUT2 = MOTOR B
   * OUT3 = MOTOR C
   */

  if (do_move)
  {
    ControlOmnidrive3Wheels::doMove(fwd_bwd, left_right);
  }
  else if (do_rotate)
  {
    ControlOmnidrive3Wheels::doRotate(rotate);
  }
  else
  {
    ControlOmnidrive3Wheels::doNothing();
  }
}

/** 
 * \brief this function implements the behaviour if a transition from mixing to failsafe is taking place
 */
void ControlOmnidrive3Wheels::transitionToFailsafeFunc()
{
  RcOut::setRcOutState(OUT1, OUTx_OFF);
  RcOut::setRcOutState(OUT2, OUTx_OFF);
  RcOut::setRcOutState(OUT3, OUTx_OFF);
}

/** 
 * \brief this function implements the behaviour if a transition from failsafe to mixing is taking place
 */
void ControlOmnidrive3Wheels::transitionToMixingFunc()
{
  RcOut::setRcOutState(OUT1, OUTx_ON);
  RcOut::setRcOutState(OUT2, OUTx_ON);
  RcOut::setRcOutState(OUT3, OUTx_ON);
}

/************************************************************************/
/* PRIVATE FUNCTIONS	                                                */
/************************************************************************/

/** 
 * \brief returns true if 1500 - deadzone_us <= pulse_duration_us <= 1500 + deadzone_us
 */
bool ControlOmnidrive3Wheels::isStickInCenterPosition(uint16_t const pulse_duration_us, uint16_t const deadzone_us)
{
  uint16_t const min_value_for_stick_in_center = CENTER_VALUE_PULSE_WIDTH_US - deadzone_us;
  uint16_t const max_value_for_stick_in_center = CENTER_VALUE_PULSE_WIDTH_US + deadzone_us;

  bool const is_stick_in_center_position = (pulse_duration_us >= min_value_for_stick_in_center)
      && (pulse_duration_us <= max_value_for_stick_in_center);

  return is_stick_in_center_position;
}

/** 
 * \brief this function controls the moving of the omnidirectional platform
 */
void ControlOmnidrive3Wheels::doMove(uint16_t const fwd_bwd, uint16_t const left_right)
{
  /* http://physics.stackexchange.com/questions/57401/omni-directional-motion-resolving-three-or-more-vectors */

  float const fx = (float) ((int16_t) (left_right) - (int16_t) (CENTER_VALUE_PULSE_WIDTH_US));
  float const fy = (float) ((int16_t) (fwd_bwd) - (int16_t) (CENTER_VALUE_PULSE_WIDTH_US));

  static float const C1 = 2.0 / 3.0;
  static float const C2 = -1.0 / 3.0;
  static float const C3 = -1.0 / sqrt(3.0);

  float const fa = fx * C1;
  float const fb = fx * C2 + fy * C3;
  float const fc = fx * C2 - fy * C3;

  uint16_t const motor_A = (uint16_t) ((int16_t) (fa) + (int16_t) (CENTER_VALUE_PULSE_WIDTH_US));
  uint16_t const motor_B = (uint16_t) ((int16_t) (fb) + (int16_t) (CENTER_VALUE_PULSE_WIDTH_US));
  uint16_t const motor_C = (uint16_t) ((int16_t) (fc) + (int16_t) (CENTER_VALUE_PULSE_WIDTH_US));

  ControlOmnidrive3Wheels::setMotorA(motor_A);
  ControlOmnidrive3Wheels::setMotorB(motor_B);
  ControlOmnidrive3Wheels::setMotorC(motor_C);
}

/** 
 * \brief this function controls the rotation of the omnidirectional platform
 */
void ControlOmnidrive3Wheels::doRotate(uint16_t const rotate)
{
  ControlOmnidrive3Wheels::setMotorA(rotate);
  ControlOmnidrive3Wheels::setMotorB(rotate);
  ControlOmnidrive3Wheels::setMotorC(rotate);
}

/** 
 * \brief absolutely do nothing - all outputs are at 1500 (neutral value)
 */
void ControlOmnidrive3Wheels::doNothing()
{
  ControlOmnidrive3Wheels::setMotorA(CENTER_VALUE_PULSE_WIDTH_US);
  ControlOmnidrive3Wheels::setMotorB(CENTER_VALUE_PULSE_WIDTH_US);
  ControlOmnidrive3Wheels::setMotorC(CENTER_VALUE_PULSE_WIDTH_US);
}

/** 
 * \brief control the three motors
 */
void ControlOmnidrive3Wheels::setMotorA(uint16_t const pulse_duration_us)
{
  RcOut::setPwmPulseDurationUs(OUT1, pulse_duration_us);
}

void ControlOmnidrive3Wheels::setMotorB(uint16_t const pulse_duration_us)
{
  RcOut::setPwmPulseDurationUs(OUT2, pulse_duration_us);
}

void ControlOmnidrive3Wheels::setMotorC(uint16_t const pulse_duration_us)
{
  RcOut::setPwmPulseDurationUs(OUT3, pulse_duration_us);
}

#endif
