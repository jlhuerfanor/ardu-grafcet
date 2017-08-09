/*
 * Timer.cpp
 *
 *  Created on: 8/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

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
		this->elapsed += elapsedClicks;
		if(TOMILLIS(this->elapsed) >= this->delta)
		{
			if(this->action != NULL)
				this->action(TOMILLIS(this->elapsed));
			if(this->isContinous())
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

bool Timer::isContinous() const {
	return this->state & 1;
}

bool Timer::isInterrupted() {
	return !this->isEnabled() && this->elapsed != 0;
}

void Timer::setContinous(bool continous) {
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
	this->state = 0x01;
}
