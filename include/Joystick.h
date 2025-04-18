#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "Logger.h"

struct JoystickPins {
    uint8_t vrX;
    uint8_t vrY;
    uint8_t sw;
};

class Joystick {
private:
    JoystickPins _joystickPins;
    
public:
    Joystick();

    void setup();
};

#endif