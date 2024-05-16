#include "Joystick.h"

int joystickCenter = 2449;
int joystickCenterMargin = 1000;
int currentCursorY = 0;
bool joystickMoved = false;
bool changingLightOnTime = false;
bool changingLightOffTime = false;
Page currentPage = HOME_PAGE;

extern FunctionPointer relayFunctions[];

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
            switch (currentPage)
            {
            case HOME_PAGE:
                refreshHomePage = true;
            case RELAYS_PAGE:
                refreshRelaysPage = true;
                break;
            case SETTINGS_PAGE:
                refreshSettingsPage = true;
                break;
            }
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
            switch (currentPage)
            {
            case HOME_PAGE:
                refreshHomePage = true;
                break;
            case RELAYS_PAGE:
                refreshRelaysPage = true;
                break;
            case SETTINGS_PAGE:
                refreshSettingsPage = true;
                break;
            }
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
    switchPage();
    resetJoystick(joystickY);

    if (changingLightOnTime) {
        changeLightTime(lightOnTime, joystickY);        
    } else if (changingLightOffTime) {
        changeLightTime(lightOffTime, joystickY);        
    } else {        
        moveCursorUp(joystickY);
        moveCursorDown(joystickY);        
    }        
}

void handleJoystickClick() {   
    static unsigned long lastPressTime = 0;
    const unsigned long debounceDelay = 200;

    if (digitalRead(joystickPins.SW) == LOW) {
        unsigned long currentTime = millis();

        if (currentTime - lastPressTime > debounceDelay) {            
            lastPressTime = currentTime;

            switch (currentPage) {
                case HOME_PAGE:
                    handleHomePageClick();
                    break;
                case SETTINGS_PAGE:
                    handleSettingsPageClick();
                    break;
                case RELAYS_PAGE:
                    handleRelaysPageClick();
                    break;
            }
        }
    }
}

void handleHomePageClick() {
    if (currentCursorY == 3) {
        toggleAutoMode();
    }
}

void handleSettingsPageClick() {
    if (currentCursorY == 0) {
        changingLightOnTime = !changingLightOnTime;
        changingLightOffTime = false;
    } else if (currentCursorY == 1) {
        changingLightOffTime = !changingLightOffTime;
        changingLightOnTime = false;
    }
}

void handleRelaysPageClick() {
    if (!autoMode) {
        relayFunctions[currentCursorY]();
    }
}

void changeLightTime(int &lightTime, int joystickY) {
    if (joystickY < joystickCenter - joystickCenterMargin && !joystickMoved) {
        if (lightTime < 23 && (lightTime + 1) != (changingLightOnTime ? lightOffTime : lightOnTime)) {
            lightTime++;            
        }
        joystickMoved = true;
    } else if (joystickY > joystickCenter + joystickCenterMargin && !joystickMoved) {
        if (lightTime > 0 && (lightTime - 1) != (changingLightOnTime ? lightOffTime : lightOnTime)) {
            lightTime--;            
        }
        joystickMoved = true;
    }
}