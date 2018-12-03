//============================================================================
// Name        : Timer.cpp
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Defines a timer that can rise time events.
//============================================================================

#include "Timer.h"

Timer::Timer(TimerAction action, ulong delta) {
	this->action = action;
	this->elapsed = 0;
	this->state = 0;
	this->delta = delta;
}

void Timer::tick(ulong elapsedClicks) {

	if(this->isEnabled())
	{
		// cout << "> Te: " << this->elapsed << ", Td: " << elapsedClicks << endl;
		this->elapsed += elapsedClicks;
		if(TOMS(this->elapsed) >= this->delta)
		{
			if(this->action != NULL)
				this->action(TOMS(this->elapsed));
			if(this->isContinuous())
				this->reset();
			else this->disable();
		}
	}
}

void Timer::enable() {
	if(this->isInterrupted())
		this->reset();
	this->state = this->state | 2;
}

void Timer::reset() {
	this->elapsed = 0;
}

bool Timer::isEnabled() {
	return this->state & 2;
}

bool Timer::isContinuous() const {
	return this->state & 1;
}

bool Timer::isInterrupted() {
	return !this->isEnabled() && this->elapsed != 0;
}

void Timer::setContinuous(bool continous) {
	if(continous)
		this->state = this->state | 1;
	else this->state = this->state & 0xFE;
}

void Timer::disable() {
	this->state = this->state & 0xFD;
	//this->reset();
}

Timer::Timer(TimerAction action, ulong delta, bool isContinous) {
	this->action = action;
	this->elapsed = 0;
	this->delta = delta;
	this->state = (isContinous) ? 0x01 : 0x00;
}
