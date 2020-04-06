#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include "src/CounterState.h"
#include "src/CountDownState.h"
#include "src/IdleState.h"
#include "src/ButtonHandler.h"
#include "src/Logger.h"

byte state = 0;

CounterState* teethWashTimer = new CountDownState(20);
CounterState* handWashTimer = new CountDownState(120);
IdleState* idleState = new IdleState();

CounterState* activeState = NULL;

void setup() {
  // put your setup code here, to run once:

  Timer1.initialize();
  Serial.begin(9600);
  MFS.initialize(&Timer1);
  ButtonHandler::getInstance()->initialize(3);

  MFS.beep(1,0,3,3);
  gotoState(0);
}

void loop() {
  ButtonHandler::getInstance()->consume();
  activeState->nextStep();
  if (activeState->shouldStop()) {
    processStopReason();
  }
  delay(200);
}

void processStopReason() {
  const byte reason = activeState->stopReason();
  if (state == 0) {
    gotoState(reason);
    return;
  }
  if (state == 1 || state == 2) {
    gotoState(0);
    return;
  }
}

void gotoState(byte localStage) {
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
    default: {
      gotoState(0);
    }
  }
  ButtonHandler::getInstance()->resetAllButtons();
  activeState->activate();
}