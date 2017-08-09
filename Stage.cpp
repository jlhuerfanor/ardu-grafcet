/*
 * Stage.cpp
 *
 *  Created on: 7/08/2017
 *      Author: leonardo
 */

#include "Stage.h"

Stage::Stage(stageAction action) {
  this->action = action;
  this->state = STANDBY;
  this->onDeactivating = 0;
  this->onActivating = 0;
}

Stage::Stage(stageAction action, stageAction onActivating, stageAction onDeactivating) {
  this->action = action;
  this->state = STANDBY;
  this->onDeactivating = onDeactivating;
  this->onActivating = onActivating;
}
Stage::~Stage() {
  this->action = 0;
  this->onDeactivating = 0;
}

byte Stage::getState() const {
  return this->state;
}

void Stage::activate() {
  this->state = ACTIVE | TRANSITING;
}

void Stage::deactivate() {
  this->state = TRANSITING;
}

void Stage::update() {
  if (this->isActive())
  {
    if(this->isTransiting())
    {
      if(this->onActivating != NULL)
        this->onActivating();
      this->state = ACTIVE;
    }
    if(this->action != NULL)
    	this->action();
  }
  else if (this->isTransiting()) {
    if(this->onDeactivating != NULL)
      this->onDeactivating();
    this->state = STANDBY;
  }
}
bool Stage::isActive() {
  return ((this->state & ACTIVE) >> 1);
}
bool Stage::isTransiting() {
  return ((this->state & TRANSITING));
}
