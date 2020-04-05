#ifndef CountDownState_h_
#define CountDownState_h_

#include "CounterState.h"

class CountDownState : public CounterState {
  public:
    CountDownState(int seconds);
    void activate();
    void nextStep();
    void stop();
    bool shouldStop();
    int stopReason();

  private:
    void processButtons();
    int seconds;
    int currentMiliseconds;
    int stateDuration;
};
#endif