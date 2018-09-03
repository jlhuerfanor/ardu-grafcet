#ifndef STAGE_H_
#define STAGE_H_

//#include <Arduino.h>
#include "libtypes.h"

#ifndef ARDUINO
#include <cstddef>
#endif

#define ACTIVE       2
#define TRANSITING   1
#define STANDBY      0

typedef void (*StageAction)(void);

class Stage{
private:
  StageAction action;
  StageAction onDeactivating;
  StageAction onActivating;
  byte state;
public:
  Stage(StageAction action);
  Stage(StageAction action, StageAction onActivating, StageAction onDeactivating);
  virtual ~Stage();

  byte getState() const;
  void activate();
  void deactivate();
  void update();

  bool isActive();
  bool isTransiting();
};


#endif
