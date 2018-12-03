//============================================================================
// Name        : Clock.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Provides a time signal to a set of timers.
//============================================================================

#ifndef CLOCK_H_
#define CLOCK_H_

#include "Timer.h"
/*
 * Defies a class that provides a time signal to a set of timers.
 */
class Clock {
private:
	/* Saves the system time. See Timer.h for macro definition. */
	ulong currentTime;
	/* Set of timers to attatch */
	Timer * timers;
	/* Number of timers in the timer set. */
	int timerCount;
public:
	Clock(Timer * timers, int timerCount);
	/* Computes a single clock signal and rise a time event */
	void tick();
	/* Reset the Clock and all the timers in the set */
	void reset();
};

#endif /* CLOCK_H_ */
