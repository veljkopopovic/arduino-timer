#ifndef CounterState_h_
#define CounterState_h_

class CounterState {
  public:
    virtual void activate();
    virtual void nextStep();
    virtual void stop();
    virtual bool shouldStop();
    virtual int stopReason();

  protected:
    void log (const char* content);

  private:
    int stageId;
};

#endif