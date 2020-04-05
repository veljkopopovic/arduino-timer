#ifndef CountDownState_h_
#define CountDownState_h_

#include "CounterState.h"
#include <Arduino.h>

class CountDownState : public CounterState {
  public:
    CountDownState(byte seconds);
    void activate();
    void nextStep();
    void stop();
    bool shouldStop();
    byte stopReason();

  private:
    void processButtons();
    byte seconds;
    unsigned long currentMiliseconds;;
    byte stateDuration;
};
#endif