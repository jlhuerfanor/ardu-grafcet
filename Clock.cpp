//============================================================================
// Name        : Clock.cpp
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Provides a time signal to a set of timers.
//============================================================================

#include "Clock.h"

Clock::Clock(Timer* timers, int timerCount) {
	this->timers = timers;
	this->timerCount = timerCount;
	this->currentTime = NOW();
}

void Clock::tick() {
	ulong now = NOW();
	ulong delta = DELTA_TIME(this->currentTime, now);

	this->currentTime = now;

	for (int i = 0; i < timerCount; i++) {
		this->timers[i].tick(delta);
	}
}

void Clock::reset() {
	this->currentTime = NOW();
	for (int i = 0; i < this->timerCount; i++)
		this->timers[i].reset();
}
