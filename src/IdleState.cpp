#include "IdleState.h"
#include "Arduino.h"
#include <MultiFuncShield.h>

IdleState::IdleState() {
}

void IdleState::nextStep() {
  this->checkIfButtonPressed();
}

void IdleState::checkIfButtonPressed() {
  byte btn = MFS.getButton();
  if (!btn) {
    //nothing to be done
    return;
  }

  byte buttonNumber = btn & B00111111;
  //todo: move this button processing to a lib ...
  this->buttonPressed = (int)buttonNumber;
  Serial.println(this->buttonPressed, DEC);
  char data[100];
  sprintf(data, "Idle state has detected button press: %d", this->buttonPressed);
  this->log(data);
}

void IdleState::activate() {
  this->buttonPressed = -1;
  MFS.beep();
  MFS.write("gO", 1);
  delay(1000);
  MFS.write("    ");
}

void IdleState::stop() {
  MFS.beep();
  MFS.beep();
  this->buttonPressed = -1;
  this->log("Idle state stopped");
}

bool IdleState::shouldStop() {
  return this->buttonPressed > -1;
}

int IdleState::stopReason() {
  return this->buttonPressed;
}