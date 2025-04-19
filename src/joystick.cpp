#include "Joystick.h"

const int joystickCenter = 2400;
const int joystickCenterMargin = 1000;
unsigned long lastMoveTime = 0;

Joystick::Joystick(Display& display) :
    _joystickPins {
        .vrX = 4,
        .vrY = 5,
        .sw = 3
    },
    _display(display)
{}

void Joystick::setup() {
    Logger::getLogger()->log(INFO, "Joystick: Setting up");
    pinMode(_joystickPins.sw, INPUT_PULLUP);
    pinMode(_joystickPins.vrX, INPUT);
    pinMode(_joystickPins.vrY, INPUT);    
}

void Joystick::handleJoystickMovement() {
    // read the current position of the joystick
    int joystickY = analogRead(_joystickPins.vrY);            

    // move the cursor
    moveCursor(joystickY);
}

void Joystick::moveCursor(int joystickY) {
    unsigned long currentTime = millis();
    uint8_t currentCursorY = _display.getCurrentCursorY();
    
    // debounce the joystick movement to avoid multiple movement
    if (currentTime - lastMoveTime < 300) {
        return;
    }

    if (joystickY < joystickCenter - joystickCenterMargin) {        
        lastMoveTime = currentTime;
        if (currentCursorY > 0) {
            _display.setCurrentCursorY(currentCursorY - 1);
        } else {
            _display.changePage(false);
        }
    }
    else if (joystickY > joystickCenter + joystickCenterMargin) {               
        lastMoveTime = currentTime;
        if (currentCursorY < 3) {
            _display.setCurrentCursorY(currentCursorY + 1);
        } else {
            _display.changePage(true);
        }
        
    }    
}