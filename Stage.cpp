//============================================================================
// Name        : Stage.cpp
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Implements a grafcet stage.
//============================================================================

#include "Stage.h"

Stage::Stage(StageAction action) {
  this->action = action;
  this->state = STANDBY;
  this->onDeactivating = 0;
  this->onActivating = 0;
}

Stage::Stage(StageAction action, StageAction onActivating, StageAction onDeactivating) {
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
	if(!this->isActive()) {
		this->state = ACTIVE | TRANSITING;
	}
}

void Stage::deactivate() {
	if(this->isActive()) {
		this->state = TRANSITING;
	}
}

void Stage::update() {
  if (this->isActive())
  {
    if(this->isTransiting())
    {
      if(this->onActivating != NULL)
        this->onActivating();
      this->state = ACTIVE;
    } else if(this->action != NULL) {
    	this->action();
    }
  }
  else if (this->isTransiting()) {
    if(this->onDeactivating != NULL)
      this->onDeactivating();
    this->state = STANDBY;
  }
}
bool Stage::isActive() {
  return ((this->state & ACTIVE) == ACTIVE);
}
bool Stage::isTransiting() {
  return ((this->state & TRANSITING) == TRANSITING);
}
