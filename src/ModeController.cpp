#include "ModeController.h"

ModeController::ModeController(RelayController& _relayController) :
    relayController(_relayController)
{}

AutoModeState ModeController::getAutoModeState() {
    return autoModeState;
}

void ModeController::toggleAutoMode() {
    autoModeState == ON ? autoModeState = OFF : autoModeState = ON;
}

void ModeController::runAutoMode() {
    // si la temp > 26, démarre le fan
    // si la temp redescend en bas de 25, on éteint le fan


    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        // check avec les millis
    }

    int currentHour = timeinfo.tm_hour;
    if (currentHour >= sunriseHour && currentHour < sunsetHour) {
        relayController.setRelayState("TopL", RELAY_ON);
        relayController.setRelayState("BtmL", RELAY_ON);
    }
}