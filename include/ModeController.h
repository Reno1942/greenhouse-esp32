#ifndef GREENHOUSE_ESP32_MODEHANDLER_H
#define GREENHOUSE_ESP32_MODEHANDLER_H

#include <Arduino.h>

#include "RelayController.h"
#include "RTClib.h"
#include "SensorController.h"

enum AutoModeState : bool {
    OFF = false,
    ON = true
};

class ModeController {
public:
    ModeController(RelayController &_relayController, SensorController &_sensorController, RTC_DS1307 &_rtc);

    AutoModeState getAutoModeState();

    void toggleAutoMode();

    void setTimeTrackingMode(bool realTime);

    bool isDaytime();

    void runOverflowProtection(unsigned long currentTime);

    void runAutoMode();

private:
    RelayController &relayController;
    SensorController &sensorController;
    RTC_DS1307 &rtc;

    AutoModeState autoModeState = ON;
    uint8_t sunriseHour = 0;
    uint8_t sunsetHour = 18;
    bool usingRealTime = true;
    const unsigned long lightOnDuration = 18UL * 60UL * 60UL * 1000UL;
    const unsigned long fullCycle = 24UL * 60UL * 60UL * 1000UL;

    const float humidityLowerBound = 50;
    const float humidityUpperBound = 70;

    const unsigned long pumpTimeoutMs = 60000;
    unsigned long pumpOffTime = 0;
    bool pumpTimedOut = false;
};

#endif //GREENHOUSE_ESP32_MODEHANDLER_H
