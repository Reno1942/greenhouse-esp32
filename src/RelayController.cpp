#include "RelayController.h"

RelayController::RelayController() : relays{
    {
        {"TopL", {21, RELAY_OFF}},
        {"BtmL", {20, RELAY_OFF}},
        {"Fan", {23, RELAY_OFF}},
        {"Pump", {22, RELAY_OFF}},
    }
} {
}

void RelayController::setupRelays() {
    Serial.println("RelayHandler : Setting up relays");
    for (auto& [name, relay] : relays) {
        pinMode(relay.pin, OUTPUT);
        digitalWrite(relay.pin, relay.state);
    }
}

void RelayController::toggleRelay(const char* relayName) {
    for (auto& [name, relay] : relays) {
        if (strcmp(relayName, name) == 0) {
            relay.state = (relay.state == RELAY_OFF) ? RELAY_ON : RELAY_OFF;

            digitalWrite(relay.pin, relay.state);
            return;
        }
    }
}

std::array<RelayEntry, 4>& RelayController::getRelays() {
    return relays;
}
