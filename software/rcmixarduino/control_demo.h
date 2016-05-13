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

#ifndef CONTROLDEMO_H_
#define CONTROLDEMO_H_

/************************************************************************/
/* INCLUDES                                                             */
/************************************************************************/

#include <stdbool.h>

#include "config.h"

#ifdef CONFIG_USE_CONTROL_DEMO

/************************************************************************/
/* PUBLIC PROTOTYPES                                                    */
/************************************************************************/

class ControlDemo
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
	ControlDemo() { }

};

#endif

#endif /* CONTROLDEMO_H_ */
