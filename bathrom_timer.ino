#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include "src/CounterState.h"
#include "src/CountDownState.h"
#include "src/IdleState.h"

int stage = 0;
int millisReference = 0;
int displayVal = -1;
int secondsTop = -1;

CounterState* teethWashTimer = new CountDownState(1, 20);
CounterState* handWashTimer = new CountDownState(3, 120);
IdleState* idleState = new IdleState(0);

CounterState* activeState = NULL;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  Serial.begin(9600);
  MFS.initialize(&Timer1);
  MFS.beep(1,0,3,3);
  gotoIdle();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (10 == stage) {
    waitForButtonsToBeReleased();
    return;
  }
  if (0 == stage) {
    checkInitButtonPressed();
    return;
  }

  if (1 == stage || 2 == stage) {
    updateCounter();
  }

  if (shouldStop()) {
    stop();
    return;
  }

  activeState->processButtons();
  sendStateToDisplay();
  checkResetButtonCombination();
  delay(20);
}

void checkInitButtonPressed() {
  byte btn = MFS.getButton();
  if (!btn) {
    return;
  }

  byte buttonNumber = btn & B00111111;
  byte buttonAction = btn & B11000000;

  Serial.print("Button pressed: ");
  Serial.println(buttonNumber, DEC);

  switch(buttonNumber) {
    case 1: {
      secondsTop = 120;
      setStage(1);
      activeState = teethWashTimer;
      activeState->activate();
      return;
    }
    case 2: {
      secondsTop = 20;
      setStage(2);
      activeState = handWashTimer;
      activeState->activate();
      return;
    }
  }

}

void setStage(int localStage) {
  stage = localStage;
  Serial.print("Button one pressed -> counter");
  Serial.println(stage, DEC);
  millisReference = millis();
  MFS.beep();
}

void updateCounter() {
  int current = millis();
  if (current - millisReference < 1000) {
    //nothing to be done
    return;
  }

  millisReference = current;
  secondsTop--;
}

void checkResetButtonCombination() {
  byte btn = MFS.getButton();
  if (!btn) {
    return;
  }

  byte buttonNumber2 = btn & B00111111;
  byte buttonAction2 = btn & B11000000;

  byte btn2 = MFS.getButton();
  if (!btn2) {
    MFS.queueButton(btn);
    return;
  }

  byte buttonNumber1 = btn2 & B00111111;
  byte buttonAction1 = btn2 & B11000000;
  Serial.print("Button combination detected: ");
  Serial.print(buttonNumber2, DEC);
  Serial.print(", ");
  Serial.println(buttonNumber1, DEC);
  MFS.write("----");
  stage = 0;
  delay(1000);
  stop();
}

void waitForButtonsToBeReleased() {
}

boolean shouldStop() {
  return secondsTop == 0;
}

void stop() {
  displayVal = -1;
  secondsTop = -1;
  MFS.resetButtonQueue();
  gotoIdle();
}

void resetScreen() {
  Serial.println("Will reset screen");
}

void sendStateToDisplay() {
  if (displayVal == secondsTop) {
    //nothing to be done
    return;
  }

  displayVal = secondsTop;
  MFS.write(displayVal);
}

void gotoIdle() {
  activeState = idleState;
  idleState->activate();
  stage = 0;
}
