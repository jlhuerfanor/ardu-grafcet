/*
 * grafcet.h
 *
 *  Created on: 7/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

#ifndef GRAFCET_H_
#define GRAFCET_H_

#include "Stage.h"
#include "Transition.h"
#include "Clock.h"

typedef bool (*Predicate) (int);

class Grafcet{
private:
  Transition * transitions;
  int transitionCount;
  Stage * stages;
  int stageCount;
  Predicate predicate;
  int initialState;
  Clock * clock;
public:
  Grafcet(Transition * transitions, int transitionCount, Stage * stages, int stageCount, Predicate predicates);

  void setup();
  void loop();
  void reset();
  int getInitialState() const;
  void setInitialState(int initialState);
  Predicate getPredicate() const;
  int getStageCount() const;
  Stage* getStages();
  int getTransitionCount() const;
  Transition* getTransitions();
  Clock * getClock();
  void setClock(Clock* clock);
};

#endif /* GRAFCET_H_ */
