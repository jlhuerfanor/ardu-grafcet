/*
 * Timer.h
 *
 *  Created on: 8/08/2017
 *      Author: leonardo
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifndef ARDUINO
#include <ctime>
#endif
#include "libtypes.h"

typedef void (*TimerAction)(ulong);

#ifndef ARDUINO
#define NOW() ((ulong)(clock()))
#define TOFMS(time) ((time) * 1000.0 / CLOCKS_PER_SEC)
#define TOMS(time) (time * 1000 / CLOCKS_PER_SEC)
#else
#define NOW() ((ulong)micros())
#define TOFMS(time) ((time) / 1000.0)
#define TOMS(time) ((time) / 1000)
#endif
#define DELTA_TIME(t1, t2) (((t2) < (t1))? \
	(ULONG_MAX - (t1) + (t2) + 1) : \
	(t2) - (t1))

class Timer {
private:
	ulong elapsed;
	TimerAction action;
public:
	ulong delta;
	byte state;

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
