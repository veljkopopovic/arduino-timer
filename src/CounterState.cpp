#include "CounterState.h"
#include <MultiFuncShield.h>

CounterState::CounterState(int stageId) {
  this->stageId = stageId;
}

int CounterState::getStateID() {
  return this->stageId;
}

void CounterState::processButtons() {
  byte btn = MFS.getButton();

  if (!btn) {
    //nothing to be done
    return;
  }

  byte buttonNumber = btn & B00111111;
  byte buttonAction = btn & B11000000;

  Serial.print("BUTTON NUMBER: ");
  Serial.print(buttonNumber, DEC);
  Serial.print(" BUTTON ACTION: ");
  Serial.println(buttonAction, DEC);
}

void CounterState::log(const char* data) {
  Serial.println(data);
}
