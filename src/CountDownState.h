#ifndef CountDownState_h_
#define CountDownState_h_

#include "CounterState.h"

class CountDownState : public CounterState {
  public:
    CountDownState(int stage, int seconds);
    void activate();
    bool nextStep();
    void stop();

  private:
    int seconds;
    int currentMiliseconds;
};
#endif