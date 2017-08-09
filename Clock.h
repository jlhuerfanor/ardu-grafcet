/*
 * Clock.h
 *
 *  Created on: 8/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "Timer.h"

class Clock {
private:
	ulong currentTime;
	Timer * timers;
	int timerCount;
public:
	Clock(Timer * timers, int timerCount);

	void tick();
	void reset();
};

#endif /* CLOCK_H_ */
