//============================================================================
// Name        : Grafcet.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Container for a grafcet definition.
//============================================================================

#ifndef GRAFCET_H_
#define GRAFCET_H_

#include "Stage.h"
#include "Transition.h"
#include "Clock.h"

#define GRAFCET_STATE_INITIALIZED 		(BIT(0))
#define GRAFCET_STATE_ACTIVE			(BIT(1))

typedef bool (*Predicate)(int);
typedef void (*Action)();
typedef void (*PerTransition)(int);
typedef void (*PerEvaluation)(int, bool evaluated);
typedef void (*PerActivation)(int, bool activated);

class Grafcet {
private:

	Transition * transitions;
	int transitionCount;
	Stage * stages;
	int stageCount;
	Predicate predicate;
	Action onStop;
	int initialState;
	Clock * clock;
	byte state;
public:
	int vector = 0;
	PerActivation perActivation;
	PerTransition perTransition;
	PerEvaluation perEvaluation;

	Grafcet(Transition * transitions, int transitionCount, Stage * stages,
			int stageCount, Predicate predicates);

	void setup();
	void loop();
	void reset();
	void stop();
	int getInitialState() const;
	void setInitialState(int initialState);
	Predicate getPredicate() const;
	int getStageCount() const;
	Stage* getStages();
	int getTransitionCount() const;
	Transition* getTransitions();
	Clock * getClock();
	void setClock(Clock* clock);
	Action getOnStop() const;
	void setOnStop(Action onStop);
	bool isInitialized();
	bool isStopped();
	bool isActive();
};

#endif /* GRAFCET_H_ */
