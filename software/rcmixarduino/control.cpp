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

#include "control.h"

#include <util/delay.h>

#include "led.h"

/************************************************************************/
/* PUBLIC FUNCTIONS	                                                    */
/************************************************************************/

/** 
 * \brief The Constructor is handed over function pointers which point to the 
 * concrete implementation of the desired mixing functionality.
 */
Control::Control(controlIsGoodFunc isGoodFunc, controlFailsafeFunc failsafeFunc, controlMixingFunc mixingFunc,
    controlOnTransitionToFailsafe transitionToFailsafeFunc, controlOnTransitionToMixing transitionToMixingFunc) :
    _state(FAILSAFE), _isGoodFunc(isGoodFunc), _failsafeFunc(failsafeFunc), _mixingFunc(mixingFunc), _transitionToFailsafeFunc(
        transitionToFailsafeFunc), _transitionToMixingFunc(transitionToMixingFunc)
{

}

/** 
 * \brief This function is executed in the main loop. Here we call the 
 * concrete failsafe and mixing functions and accomplish the state 
 * transition between those states.
 */
void Control::execute()
{
  switch (_state)
  {
  case FAILSAFE:
  {
    if (_failsafeFunc != 0)
    {
      _failsafeFunc();
    }

    /* Signal failsafe state */

    toogleLed();

    _delay_ms(100);

    /* State handling */

    if (isGood())
    {
      _state = MIXING;

      if (_transitionToMixingFunc != 0)
      {
        _transitionToMixingFunc();
      }
    }
  }
    break;

  case MIXING:
  {
    if (_mixingFunc != 0)
    {
      _mixingFunc();
    }

    /* Signal active state */

    turnLedOn();

    /* State handling */

    if (!isGood())
    {
      _state = FAILSAFE;

      if (_transitionToFailsafeFunc != 0)
      {
        _transitionToFailsafeFunc();
      }
    }
  }
    break;

  default:
  {
    _state = FAILSAFE;
  }
    break;
  }
}

/************************************************************************/
/* PRIVATE FUNCTIONS	                                                */
/************************************************************************/

bool Control::isGood()
{
  if (_isGoodFunc)
  {
    return _isGoodFunc();
  }
  else
  {
    return false;
  }
}

void Control::toogleLed()
{
  static bool is_led_turned_on = true;

  if (is_led_turned_on)
  {
    Led::setState(LED_ON);
  }
  else
  {
    Led::setState(LED_OFF);
  }

  is_led_turned_on = !is_led_turned_on;
}

void Control::turnLedOn()
{
  Led::setState(LED_ON);
}
