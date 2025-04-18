#include "Joystick.h"

Joystick::Joystick() :
    _joystickPins {
        .vrX = 4,
        .vrY = 5,
        .sw = 3
    }
{}

void Joystick::setup() {
    Logger::getLogger()->log(INFO, "Joystick: Setting up");
    pinMode(_joystickPins.sw, INPUT_PULLUP);
    pinMode(_joystickPins.vrX, INPUT);
    pinMode(_joystickPins.vrY, INPUT);
    Logger::getLogger()->log(INFO, "Joystick: Set up successfully");
}