/*
 * Clock.cpp
 *
 *  Created on: 8/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

#include "Clock.h"

// LONG_MAX 
#define LONG_MAX (sizeof(ulong))

Clock::Clock(Timer* timers, int timerCount) {
	this->timers = timers;
	this->timerCount = timerCount;
	this->currentTime = NOW();
}

void Clock::tick() {
	ulong now = NOW();
	ulong delta = (now < this->currentTime)? (LONG_MAX - this->currentTime + now + 1) : now - this->currentTime;

	this->currentTime = now;

	for(int i = 0; i < timerCount; i++)
	{
		this->timers[i].tick(delta);
	}
}

void Clock::reset() {
	this->currentTime = NOW();
	for(int i = 0; i < this->timerCount; i++)
		this->timers[i].reset();
}
