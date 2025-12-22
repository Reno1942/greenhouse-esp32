#ifndef GREENHOUSE_ESP32_MODEHANDLER_H
#define GREENHOUSE_ESP32_MODEHANDLER_H

#include <Arduino.h>

enum AutoModeState : bool {
    OFF = false,
    ON = true
};

class ModeController {
public:
    ModeController();
    AutoModeState getAutoModeState();

private:
    AutoModeState autoModeState = ON;
};

#endif //GREENHOUSE_ESP32_MODEHANDLER_H