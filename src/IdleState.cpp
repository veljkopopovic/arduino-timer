#include "IdleState.h"
#include "Arduino.h"
#include <MultiFuncShield.h>

IdleState::IdleState(int stage) : CounterState(stage){

}

bool IdleState::nextStep() {
}

void IdleState::activate() {
  MFS.beep();
  MFS.write("gO", 1);
  delay(1000);
  MFS.write("    ");
}

void IdleState::stop() {
}
