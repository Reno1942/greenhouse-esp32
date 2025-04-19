#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "Logger.h"
#include "Display.h"

struct JoystickPins {
    uint8_t vrX;
    uint8_t vrY;
    uint8_t sw;
};

class Joystick {
private:
    JoystickPins _joystickPins;
    Display& _display;

public:
    Joystick(Display& display);

    void setup();

    // Handles the joystick movement
    void handleJoystickMovement();

    // Moves the cursor on the screen depending on the joystick position
    void moveCursor(int joystickY);    
};

#endif