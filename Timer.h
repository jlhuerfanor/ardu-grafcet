//============================================================================
// Name        : Timer.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Defines a timer that can rise time events.
//============================================================================


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
	/* Timer counter; counts the elapsed time between first clock tick event. */
	ulong elapsed;
	/* Function pointer to timer event handler. */
	TimerAction action;
<<<<<<< Updated upstream
=======
	/* Timer state */
	byte state;
>>>>>>> Stashed changes
public:
	/* Timespan to wait before timer event. */
	ulong delta;
	/* Defines a non-continous timer instance. */
	Timer(TimerAction action, ulong delta);
	/* Defines a timer instance. */
	Timer(TimerAction action, ulong delta, bool isContinous);
	/* Handle clock tick event. */
	void tick(ulong elapsedClicks);
	/* Set the timer state to enable, starting to listen the clock tick events. */
	void enable();
	/* Set the timer state to disable, stopping to listen the clock tick events. */
	void disable();
	/* Gets a value that indicates if the timer is enabled. */
	bool isEnabled();
	/* Resets timer counter. */
	void reset();
	/* Gets a value that indicates if the timer is interrupted. */
	bool isInterrupted();
	/* Gets a value that indicates if the timer is on continuous mode. */
	bool isContinuous() const;
	/* Sets a value that indicates if the timer is on continuous mode. */
	void setContinuous(bool continuous);
        /* Timespan to wait before timer event. */
	ulong delta;
	/* Timer state */
	byte state;
};

#endif /* TIMER_H_ */
