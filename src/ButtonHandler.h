#ifndef ButtonHandler_h_
#define ButtonHandler_h_

#include <Arduino.h>
#include "Button.h"

class ButtonHandler {
  public:
    static ButtonHandler* getInstance();
    void initialize(byte numberOfButtons);
    void consume();
    bool isButtonPressed(byte buttonID);
    bool isButtonLongPressed(byte buttonID);
    bool areAnyTwoButtonsPressed();
    bool isAnyButtonPressed();
    void resetAllButtons();
    byte getButtonPressed();
    byte getLongButtonPressed();

  private:
    ButtonHandler();
    void delegateButtonEvent(byte event);
    bool isValidIndex(byte buttonIndex);
    byte normalizeIndex(byte buttonID);
    byte denormalizeIndex(byte buttonIndex);
    static ButtonHandler* instance;
    byte numberOfButtons;
    Button** buttons;
};

#endif