#include "CountDownState.h"
#include <Arduino.h>
#include <MultiFuncShield.h>
#include "ButtonHandler.h"
#include "Logger.h"

void sendToDisplay(byte seconds) {
  MFS.write(seconds);
}

CountDownState::CountDownState(byte seconds) : CounterState() {
  this->seconds = 0;
  this->currentMiliseconds = 0;
  this->stateDuration = seconds;
}

void CountDownState::activate() {
  this->seconds = this->stateDuration;
  this->currentMiliseconds = millis();
  sendToDisplay(this->seconds);
  Logger::log("Countdown state activated");
}

void CountDownState::nextStep() {
  if (this->seconds == 0) {
    return;
  }
  this->processButtons();
  unsigned long now = millis();
  if (now - this->currentMiliseconds < 1000) {
    //nothing to be done
    return;
  }


  this->currentMiliseconds = now;
  this->seconds--;
  sendToDisplay(this->seconds);
}

void CountDownState::processButtons() {
  if (ButtonHandler::getInstance()->areAnyTwoButtonsPressed()) {
    Logger::log("Stop button combination has beeen detected");
    this->seconds = 0;
  }
}

void CountDownState::stop() {
  Logger::log("Countdown state has been stopped");
}

bool CountDownState::shouldStop() {
  return this->seconds == 0;
}

byte CountDownState::stopReason() {
  return 1;
}