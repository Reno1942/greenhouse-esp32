#include "ModeController.h"

ModeController::ModeController(RelayController &_relayController, SensorController &_sensorController,
                               RTC_DS1307 &_rtc) : relayController(_relayController),
                                                   sensorController(_sensorController),
                                                   rtc(_rtc) {
}

AutoModeState ModeController::getAutoModeState() {
    return autoModeState;
}

void ModeController::toggleAutoMode() {
    autoModeState == ON ? autoModeState = OFF : autoModeState = ON;
}

void ModeController::setTimeTrackingMode(bool realTime) {
    usingRealTime = realTime;
}

bool ModeController::getTimeTrackingMode() {
    return usingRealTime;
}


bool ModeController::isDaytime() {
    if (!usingRealTime) {
        unsigned long cyclePosition = millis() % fullCycle;
        return cyclePosition < lightOnDuration;
    }

    int currentHour = rtc.now().hour();

    if (sunriseHour < sunsetHour) {
        return (currentHour >= sunriseHour && currentHour < sunsetHour);
    }

    return (currentHour >= sunriseHour || currentHour < sunsetHour );
}

void ModeController::runOverflowProtection(unsigned long currentTime) {
    if (!sensorController.waterLevelTankReached()) {
        relayController.setRelayState("Pump", RELAY_OFF);
        return;
    }

    if (sensorController.waterLevelGutterReached()) {
        if (!pumpTimedOut) {
            Serial.println("Pump timeout starting");
            pumpOffTime = currentTime;
            pumpTimedOut = true;
        }
        relayController.setRelayState("Pump", RELAY_OFF);
    }

    if (pumpTimedOut && (currentTime - pumpOffTime >= pumpTimeoutMs)) {
        Serial.println("Pump timeout over");
        pumpTimedOut = false;
    }
}

void ModeController::runAutoMode() {

    float currentHumidity = sensorController.readHumidity();

    if (currentHumidity > humidityUpperBound) {
        relayController.setRelayState("Fan", RELAY_ON);
    }
    if (currentHumidity < humidityLowerBound) {
        relayController.setRelayState("Fan", RELAY_OFF);
    }

    if (isDaytime()) {
        relayController.setRelayState("TopL", RELAY_ON);
        relayController.setRelayState("BtmL", RELAY_ON);
    } else {
        relayController.setRelayState("TopL", RELAY_OFF);
        relayController.setRelayState("BtmL", RELAY_OFF);
    }
    if (pumpTimedOut) { return; }
    if (!sensorController.waterLevelGutterReached() && sensorController.waterLevelTankReached()) {
        relayController.setRelayState("Pump", RELAY_ON);
    }
}
