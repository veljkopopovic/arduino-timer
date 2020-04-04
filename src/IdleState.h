#ifndef IdleState_h_
#define IdleState_h_

#include "CounterState.h"

class IdleState : public CounterState {
  public:
    IdleState(int stage);
    void activate();
    bool nextStep();
    void stop();
};

#endif
