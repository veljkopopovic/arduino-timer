#ifndef IdleState_h_
#define IdleState_h_

#include "CounterState.h"

class IdleState : public CounterState {
  public:
    IdleState();
    void activate();
    void nextStep();
    void stop();
    bool shouldStop();
    int stopReason();
  private:
    void checkIfButtonPressed();
    int buttonPressed;
};

#endif
