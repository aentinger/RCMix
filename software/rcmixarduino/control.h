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

#ifndef CONTROL_H_
#define CONTROL_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdbool.h>

/************************************************************************/
/* PUBLIC TYPES                                                         */
/************************************************************************/

typedef bool (*controlIsGoodFunc)             (void); /* This function is used to determine wether we are in failsafe or in mixing mode */
typedef void (*controlFailsafeFunc)           (void); /* This function is executed upon occurence of an failsafe event */
typedef void (*controlMixingFunc)             (void); /* This function is executed in normal mixing mode */
typedef void (*controlOnTransitionToFailsafe) (void); /* This function is called on the transition from mixing to failsafe mode */
typedef void (*controlOnTransitionToMixing)   (void); /* This function is called on the transition from failsafe to mixing mode */

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class Control
{

public:

  /**
   * \brief The Constructor is handed over function pointers which point to the
   * concrete implementation of the desired mixing functionality.
   */
  Control(controlIsGoodFunc isGoodFunc, controlFailsafeFunc failsafeFunc, controlMixingFunc mixingFunc,
      controlOnTransitionToFailsafe transitionToFailsafeFunc, controlOnTransitionToMixing transitionToMixingFunc);

  /**
   * \brief This function is executed in the main loop. Here we call the
   * concrete failsafe and mixing functions and accomplish the state
   * transition between those states.
   */
  void execute();

private:

  enum
  {
    FAILSAFE, MIXING
  } _state;

  controlIsGoodFunc               _isGoodFunc;
  controlFailsafeFunc             _failsafeFunc;
  controlMixingFunc               _mixingFunc;
  controlOnTransitionToFailsafe   _transitionToFailsafeFunc;
  controlOnTransitionToMixing     _transitionToMixingFunc;

  bool isGood();
  void toogleLed();
  void turnLedOn();
};

#endif /* CONTROL_H_ */
