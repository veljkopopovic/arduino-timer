#ifndef CounterState_h_
#define CounterState_h_

class CounterState {
  public:
    CounterState(int);
    virtual void activate();
    virtual bool nextStep();
    virtual void stop();
    void processButtons();

  protected:
    int getStateID();
    void log (const char* data);

  private:
    int stageId;
    bool isActive;
};

#endif