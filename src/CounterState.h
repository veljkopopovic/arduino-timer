#ifndef CounterState_h_
#define CounterState_h_

#include <Arduino.h>

class CounterState {
  public:
    virtual void activate();
    virtual void nextStep();
    virtual void stop();
    virtual bool shouldStop();
    virtual byte stopReason();

  protected:
    void log (const char* content);

  private:
    byte stageId;
};

#endif