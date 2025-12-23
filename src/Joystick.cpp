#include "Display.h"
#include "Joystick.h"

Joystick::Joystick(Display& _display, RelayController& _relayController, ModeController& _modeController) :
    joystickPins{
        .vrX = 4,
        .vrY = 5,
        .sw = 3
    },
    display(_display),
    relayController(_relayController),
    modeController(_modeController)
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

void Joystick::handleJoystickClick(unsigned long currentTime) {
    const int debounceDelayMs = 200;

    if (digitalRead(joystickPins.sw) == LOW) {
        if (currentTime - lastClickTime < debounceDelayMs) { return; }
        lastClickTime = currentTime;
        uint8_t cursorPosition = display.getCursorPosition();
        AutoModeState autoModeState = modeController.getAutoModeState();

        switch (cursorPosition) {
            case 0:
                modeController.toggleAutoMode();
                break;
            case 1:
                if (autoModeState == OFF) {
                    relayController.toggleRelay("TopL");
                }
                break;
            case 2:
                if (autoModeState == OFF) {
                    relayController.toggleRelay("BtmL");
                }
                break;
            case 3:
                if (autoModeState == OFF) {
                    relayController.toggleRelay("Fan");
                }
                break;
            case 4:
                if (autoModeState == OFF) {
                    relayController.toggleRelay("Pump");
                }
                break;
            default: break;
        }
    }
}
