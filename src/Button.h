#ifndef Button_h_
#define Button_h_

#include <Arduino.h>

class Button {
  public:
    Button();
    void reset();
    bool isPressedNow();
    bool isLongPressedNow();
    byte getPressedCount();
    byte getLongPressedCount();

    void registerDown();
    void registerUp();
    void registerLong();
    void registerLongUp();

  private:
    bool pressed = false;
    bool longPressed = false;
    byte pressCount = 0;
    byte longPressCount = 0;
};

#endif