#ifndef GREENHOUSE_ESP32_JOYSTICK_H
#define GREENHOUSE_ESP32_JOYSTICK_H
#include <Arduino.h>

struct JoystickPins {
    uint8_t vrX;
    uint8_t vrY;
    uint8_t sw;
};

class Joystick {
public:
    Joystick(Display& _display, RelayController& _relayController, ModeController& _modeController);
    void setup();
    void handleJoystickMovement(unsigned long currentTime);
    void handleJoystickClick(unsigned long currentTime);

private:
    JoystickPins joystickPins;
    Display& display;
    RelayController& relayController;
    ModeController& modeController;

    const int center = 2500; // center position of the joystick
    const int centerMargin = 1000; // margin to force comeback to center position
    const int moveDelayMs = 300; // delay to avoid double movement
    unsigned long lastMoveTime = 0;
    unsigned long lastClickTime = 0;
};

#endif //GREENHOUSE_ESP32_JOYSTICK_H