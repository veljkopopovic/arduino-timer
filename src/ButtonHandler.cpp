#include "ButtonHandler.h"
#include <MultiFuncShield.h>
#include <Arduino.h>
#include "Button.h"

ButtonHandler* ButtonHandler::instance = NULL;

ButtonHandler* ButtonHandler::getInstance() {
  if(!instance) {
    instance = new ButtonHandler();
  }
  return instance;
}

ButtonHandler::ButtonHandler() {
}

void ButtonHandler::initialize(byte numberOfButtons) {
  Button* buttons[numberOfButtons] = {};
  for (byte i = 0; i<numberOfButtons; i++) {
    buttons[i] = new Button();
  }
  this->buttons = buttons;
  this->numberOfButtons = numberOfButtons;
}

void ButtonHandler::consume() {
  byte btn;
  while (btn = MFS.getButton()) {
    this->delegateButtonEvent(btn);
  }
}

bool ButtonHandler::isValidIndex(byte index) {
  return index >= 0 && index < this->numberOfButtons;
}

void ButtonHandler::delegateButtonEvent(byte event) {
  byte buttonNumber = (event & B00111111)-1;
  byte buttonAction = (event & B11000000) >> 6;
  if (!this->isValidIndex(buttonNumber)) {
    return;
  }

  Button* btn = this->buttons[buttonNumber];
  switch (buttonAction) {
    case 0: {
      btn->registerDown();
      break;
    }
    case 1: {
      btn->registerUp();
      break;
    }

    case 2: {
      btn->registerLong();
      break;
    }

    case 3: {
      btn->registerLongUp();
      break;
    }
  }
}

byte ButtonHandler::normalizeIndex(byte buttonID) {
  return buttonID-1;
}

byte ButtonHandler::denormalizeIndex(byte buttonIndex) {
  return buttonIndex+1;
}

bool ButtonHandler::isButtonPressed(byte buttonID) {
  byte buttonIndex = this->normalizeIndex(buttonID);
  if (!this->isValidIndex(buttonIndex)) {
    return false;
  }

  return this->buttons[buttonIndex]->isPressedNow();
}

bool ButtonHandler::isButtonLongPressed(byte buttonID) {
  byte buttonIndex = this->normalizeIndex(buttonID);
  if (!this->isValidIndex(buttonIndex)) {
    return false;
  }

  return this->buttons[buttonIndex]->isLongPressedNow();
}

bool ButtonHandler::areAnyTwoButtonsPressed() {
  bool onePressed = false;
  bool isPressed = false;
  for (byte i = 0; i < this->numberOfButtons; i++) {
    isPressed = this->buttons[i]->isPressedNow();

    if (!isPressed) {
      continue;
    }

    if (!onePressed) {
      onePressed = true;
      continue;
    }

    //isPressed == true && onePressed == true
    return true;
  }
  return false;
}

void ButtonHandler::resetAllButtons() {
  for (byte i = 0; i < this->numberOfButtons; i++) {
    this->buttons[i]->reset();
  }
}

byte ButtonHandler::getButtonPressed() {
  for (byte i = 0; i < this->numberOfButtons; i++) {
    if (this->buttons[i]->isPressedNow()) {
      return this->denormalizeIndex(i);
    }
  }
  return 0;
}

byte ButtonHandler::getLongButtonPressed() {
  for (byte i = 0; i < this->numberOfButtons; i++) {
    if (this->buttons[i]->isLongPressedNow()) {
      return this->denormalizeIndex(i);
    }
  }
  return 0;
}