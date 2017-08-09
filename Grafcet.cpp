/*
 * grafcet.cpp
 *
 *  Created on: 7/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */

#include "Grafcet.h"

int Grafcet::getInitialState() const {
  return initialState;
}

void Grafcet::setInitialState(int initialState) {
  this->initialState = initialState;
}

Predicate Grafcet::getPredicate() const {
  return predicate;
}

int Grafcet::getStageCount() const {
  return stageCount;
}

Stage* Grafcet::getStages() {
  return stages;
}

int Grafcet::getTransitionCount() const {
  return transitionCount;
}

Grafcet::Grafcet(Transition* transitions, int transitionCount, Stage* stages,
    int stageCount, Predicate predicates) {
  this->transitions = transitions;
  this->transitionCount = transitionCount;
  this->stages = stages;
  this->stageCount = stageCount;
  this->predicate = predicates;
  this->initialState = 0;
  this->clock = 0;
}

void Grafcet::loop() {
  int i, j, index;
  
  if(this->clock != NULL) this->clock->tick();
  // Transition evaluation
  for (i = 0; i < this->transitionCount; i++) {
    Transition *ti = (this->getTransitions() +i);
    bool evaluate = true;

    for (j = 0; j < ti->getParentCount(); j++) {
      index = ti->getParentIndices()[j];
      evaluate = evaluate && this->stages[index].isActive();
    }
    if (evaluate && this->predicate(i)) {
      for (j = 0; j < ti->getParentCount(); j++) {
        index = ti->getParentIndices()[j];
        this->stages[index].deactivate();
      }
      for (j = 0; j < ti->getChildrenCount(); j++) {
        index = ti->getChildrenIndices()[j];
        this->getStages()[index].activate();
      }
    }
  }
  // Stage evaluation
  for (i = 0; i < this->stageCount; i++) {
    this->stages[i].update();
  }
}

void Grafcet::setup()
{
  this->reset();
}

void Grafcet::reset() {
  for (int i = 0; i < this->stageCount; i++) {
    this->stages[i].deactivate();
    this->stages[i].update();
  }
  if(this->clock != NULL) this->clock->reset();
  this->stages[this->initialState].activate();
  this->stages[this->initialState].update();
}

Clock* Grafcet::getClock(){
	return clock;
}

void Grafcet::setClock(Clock* clock) {
	this->clock = clock;
}

Transition* Grafcet::getTransitions(){
  return transitions;
}
