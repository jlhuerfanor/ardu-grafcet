/*
 * Transition.h
 *
 *  Created on: 7/08/2017
 *      Author: Jerson Huerfano <jleonardo04@hotmail.com>
 */
 
#ifndef TRANSITION_H_
#define TRANSITION_H_

class Transition{
private:
  // on sync association, multiple parents are allowed
  // and must be active to evaluate the predicate.
  int * parentIndices;
  int parentCount;
  // On sync association, multiple subsequent stages are allowed.
  int * childrenIndices;
  int childrenCount;
public:

  Transition(int * indices, int parentCount, int childrenCount);
  virtual ~Transition();

  int getChildrenCount() const;
  int* getChildrenIndices() const;
  int getParentCount() const;
  int* getParentIndices() const;
};

#endif
