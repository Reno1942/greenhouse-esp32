#include "RelayHandler.h"

RelayHandler::RelayHandler() :
    _relayPins{
        .topLight = 21,
        .bottomLight = 20,
        .fan = 23,
        .pump = 22
    }
{}

void RelayHandler::setupRelays() {
    Logger::getLogger()->log(INFO, "Relays : Setting up");

    pinMode(_relayPins.topLight, OUTPUT);
    pinMode(_relayPins.bottomLight, OUTPUT);
    pinMode(_relayPins.pump, OUTPUT);
    pinMode(_relayPins.fan, OUTPUT);    

    digitalWrite(_relayPins.topLight, RELAY_OFF);
    digitalWrite(_relayPins.bottomLight, RELAY_OFF);
    digitalWrite(_relayPins.fan, RELAY_OFF);
    digitalWrite(_relayPins.pump, RELAY_ON);
}

void RelayHandler::toggleRelay(uint8_t relayPin) {
    RelayState state = RelayState(digitalRead(relayPin));
    state = (state == RELAY_ON) ? RELAY_OFF : RELAY_ON;
    digitalWrite(relayPin, state);
    Logger::getLogger()->log(INFO, "Relay " + String(relayPin) + " turned " + (state == RELAY_ON ? "ON" : "OFF"));
}