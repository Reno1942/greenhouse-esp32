#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include <Arduino.h>


struct JoystickPins {
    uint8_t vrX;
    uint8_t vrY;
    uint8_t sw;
};

class JoystickHandler {
private:
    JoystickPins _joystickPins;
    
public:
    JoystickHandler();
};

#endif