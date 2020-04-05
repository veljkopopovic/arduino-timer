#include "Button.h"

Button::Button() {
}

void Button::reset() {
  this->pressed = false;
  this->longPressed = false;
  this->pressCount = 0;
  this->longPressCount = 0;
}

bool Button::isPressedNow() {
  return this->pressed;
}

bool Button::isLongPressedNow() {
  return this->longPressed;
}

byte Button::getPressedCount() {
  return this->pressCount;
}

byte Button::getLongPressedCount() {
  return this->longPressCount;
}

void Button::registerDown() {
  this->pressed = true;
}

void Button::registerUp() {
  this->pressed = false;
  this->pressCount++;
}

void Button::registerLong() {
  this->longPressed = true;
}

void Button::registerLongUp() {
  this->registerUp();
  this->longPressed = false;
  this->longPressCount++;
}