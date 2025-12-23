#ifndef GREENHOUSE_ESP32_MODEHANDLER_H
#define GREENHOUSE_ESP32_MODEHANDLER_H

#include <Arduino.h>

#include "RelayController.h"

enum AutoModeState : bool {
    OFF = false,
    ON = true
};

class ModeController {
public:
    ModeController(RelayController& _relayController);
    AutoModeState getAutoModeState();
    void toggleAutoMode();
    void runAutoMode();

private:
    RelayController& relayController;

    AutoModeState autoModeState = ON;
    uint8_t sunriseHour = 0;
    uint8_t sunsetHour = 18;
};

#endif //GREENHOUSE_ESP32_MODEHANDLER_H