#include "CountDownState.h"
#include <Arduino.h>
#include <MultiFuncShield.h>

CountDownState::CountDownState(int seconds) : CounterState() {
  this->seconds = 0;
  this->currentMiliseconds = 0;
  this->stateDuration = seconds;
}

void CountDownState::activate() {
  this->seconds = this->stateDuration;
  this->currentMiliseconds = millis();
  this->log("Countdown state activated");
}

void CountDownState::nextStep() {
  this->processButtons();
  int now = millis();
  if (now - this->currentMiliseconds < 1000) {
    //nothing to be done
    return;
  }

  this->currentMiliseconds = now;
  this->seconds--;
  MFS.write(this->seconds);
}

void CountDownState::processButtons() {
  //TODO
}

void CountDownState::stop() {
  this->log("Countdown state has been stopped");
}

bool CountDownState::shouldStop() {
  return this->seconds == -1;
}

int CountDownState::stopReason() {
  return 1;
}