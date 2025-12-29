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

bool ModeController::isDaytime() {
    if (usingRealTime) {
        int currentHour = rtc.now().hour();
        return (currentHour >= sunriseHour && currentHour <= sunsetHour);
    }

    unsigned long cyclePosition = millis() % fullCycle;
    return cyclePosition < lightOnDuration;
}

void ModeController::runOverflowProtection(unsigned long currentTime) {
    if (!sensorController.waterLevelTankReached()) {
        Serial.println("Water level tank reached");
        relayController.setRelayState("Pump", RELAY_OFF);
        return;
    }

    if (sensorController.waterLevelGutterReached()) {
        //Serial.println("Water level gutter reached");
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
    if (pumpTimedOut) { return; }
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

    if (!sensorController.waterLevelGutterReached() && sensorController.waterLevelTankReached()) {
        relayController.setRelayState("Pump", RELAY_ON);
    }
}
