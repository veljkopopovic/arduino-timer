#include "CountDownState.h"
#include <Arduino.h>

CountDownState::CountDownState(int stage, int seconds) : CounterState(stage) {
  this->seconds = seconds;
  this->currentMiliseconds = 0;
}

void CountDownState::activate() {
  this->currentMiliseconds = millis();
  Serial.print("Stage with id ");
  Serial.print(this->getStateID(), DEC);
  Serial.println(" has been activated.");
}

bool CountDownState::nextStep() {
  this->processButtons();
  int now = millis();
  if (now = this->currentMiliseconds < 1000) {
    //nothing to be done
    return false;
  }

  this->currentMiliseconds = now;
  this->seconds--;
  return true;
}

void CountDownState::stop() {
}
