/*
 * Timer.h
 *
 *  Created on: 8/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

#ifndef TIMER_H_
#define TIMER_H_

//#include <ctime>
#include <Arduino.h>
#include "libtypes.h"

typedef unsigned long ulong;
typedef void (*TimerAction)(ulong);

//#define NOW() ((ulong)(clock()))
//#define TOMILLIS(time) (time * 1000 / CLOCKS_PER_SEC)
#define NOW() ((ulong)millis())
#define TOMILLIS(time) (time)

class Timer {
private:
	ulong elapsed;
	ulong delta;
	byte state;
	TimerAction action;
public:
	Timer(TimerAction action, ulong delta);
	Timer(TimerAction action, ulong delta, bool isContinous);

	void tick(ulong elapsedClicks);
	void enable();
	void disable();
	bool isEnabled();
	void reset();
	bool isInterrupted();
	bool isContinous() const;
	void setContinous(bool continous);
};

#endif /* TIMER_H_ */
