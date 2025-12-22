#include "Display.h"
#include "Joystick.h"

Joystick::Joystick(Display& _display) :
    joystickPins{
        .vrX = 4,
        .vrY = 5,
        .sw = 3
    },
    display(_display)
{}

void Joystick::setup() {
    Serial.println("Joystick: Setting up");
    pinMode(joystickPins.sw, INPUT_PULLUP);
    pinMode(joystickPins.vrX, INPUT);
    pinMode(joystickPins.vrY, INPUT);
}

void Joystick::handleJoystickMovement(unsigned long currentTime) {
    int joystickY = analogRead(joystickPins.vrY);

    if (currentTime - lastMoveTime < moveDelayMs) { return; }

    if (joystickY < center - centerMargin) {
        lastMoveTime = currentTime;
        display.moveCursor(UP);
    }
    else if (joystickY > center + centerMargin) {
        lastMoveTime = currentTime;
        display.moveCursor(DOWN);
    }
}