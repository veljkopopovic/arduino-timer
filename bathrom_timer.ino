#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include "src/CounterState.h"
#include "src/CountDownState.h"
#include "src/IdleState.h"

int state = 0;

CounterState* teethWashTimer = new CountDownState(20);
CounterState* handWashTimer = new CountDownState(120);
IdleState* idleState = new IdleState();

CounterState* activeState = NULL;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  Serial.begin(9600);
  MFS.initialize(&Timer1);
  MFS.beep(1,0,3,3);
  gotoState(0);
}

void loop() {
  activeState->nextStep();
  if (activeState->shouldStop()) {
    processStopReason();
  }
  delay(200);
}

void processStopReason() {
  const int reason = activeState->stopReason();
  if (state == 0) {
    gotoState(reason);
    return;
  }
  if (state == 1 || state == 2) {
    gotoState(0);
    return;
  }
}

void gotoState(int localStage) {
  state = localStage;
  Serial.print("About to activate state ");
  Serial.println(state, DEC);
  MFS.beep();
  if (activeState) {
    activeState->stop();
  }
  switch (localStage) {
    case 0: {
      activeState = idleState;
      break;
    }
    case 1: {
      activeState = teethWashTimer;
      break;
    }

    case 2: {
      activeState = handWashTimer;
      break;
    }
  }
  activeState->activate();
}