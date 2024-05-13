#include "Joystick.h"

int joystickCenter = 2449;
int joystickCenterMargin = 1000;
int currentCursorY = 0;
bool joystickMoved = false;
Page currentPage = HOME_PAGE;

JoystickPins joystickPins;

void setupJoystick() {
    pinMode(joystickPins.SW, INPUT_PULLUP);
    pinMode(joystickPins.VRx, INPUT);
    pinMode(joystickPins.VRy, INPUT);
}

void resetJoystick(int joystickY) {
    if (abs(joystickY - joystickCenter) <= joystickCenterMargin) {
        joystickMoved = false;
    }
}

void moveCursorUp(int joystickY) {
    if (joystickY < joystickCenter - joystickCenterMargin && !joystickMoved) {        
        if (currentCursorY > 0) {
            currentCursorY--;
        } else {
            clearScreen();
            currentPage = currentPage == HOME_PAGE ? SETTINGS_PAGE : static_cast<Page>(currentPage - 1);
            currentCursorY = 3;
        }
        joystickMoved = true;
    }
}

void moveCursorDown(int joystickY) {
    if (joystickY > joystickCenter + joystickCenterMargin && !joystickMoved) {
        if (currentCursorY < 3) {
            currentCursorY++;        
        } else {
            clearScreen();
            currentPage = static_cast<Page>((currentPage + 1) % PAGE_COUNT);
            currentCursorY = 0;
        }        
        joystickMoved = true;
    }
}

void switchPage() {
    switch (currentPage)
        {
        case HOME_PAGE:        
            displayHomePage();
            break;
        case RELAYS_PAGE:        
            displayRelaysPage();
            break;
        case SETTINGS_PAGE:        
            displaySettingsPage();
            break;
        }
}

void handleJoystickControl() {
    int joystickY = analogRead(joystickPins.VRy);

    resetJoystick(joystickY);
    moveCursorUp(joystickY);
    moveCursorDown(joystickY);
    switchPage();
}