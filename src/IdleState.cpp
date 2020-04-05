#include "IdleState.h"
#include "Arduino.h"
#include <MultiFuncShield.h>
#include "ButtonHandler.h"

IdleState::IdleState() {
}

void IdleState::nextStep() {
  byte pressed = ButtonHandler::getInstance()->getButtonPressed();
  if (0 == pressed) {
    //nothing to be done
    return;
  }
  this->buttonPressed = pressed;
}

void IdleState::activate() {
  this->buttonPressed = 0;
  MFS.beep();
  MFS.write("gO", 1);
  delay(1000);
  MFS.write("    ");
}

void IdleState::stop() {
  MFS.beep();
  MFS.beep();
  this->buttonPressed = 0;
  this->log("Idle state stopped");
}

bool IdleState::shouldStop() {
  return this->buttonPressed > 0;
}

byte IdleState::stopReason() {
  return this->buttonPressed;
}