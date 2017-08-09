/*
 * Transtition.cpp
 *
 *  Created on: 7/08/2017
 *      Author: leonardo
 */
 
#include "Transition.h"


int Transition::getChildrenCount() const {
  return childrenCount;
}

int* Transition::getChildrenIndices() const {
  return childrenIndices;
}

int Transition::getParentCount() const {
  return parentCount;
}

Transition::Transition(int* indices, int parentCount, int childrenCount) {
  this->parentIndices = indices;
  this->parentCount = parentCount;
  this->childrenIndices = (indices + parentCount);
  this->childrenCount = childrenCount;
}

Transition::~Transition() {
}

int* Transition::getParentIndices() const {
  return parentIndices;
}
