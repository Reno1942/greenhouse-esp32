#include "RelayHandler.h"

RelayHandler::RelayHandler() {
    _relays[0] = {"X   TopL", 21, RELAY_OFF};
    _relays[1] = {"X   BtmL", 20, RELAY_OFF};
    _relays[2] = {"X   Fan", 23, RELAY_OFF};
    _relays[3] = {"X   Pump", 22, RELAY_OFF};    
}

void RelayHandler::setupRelays() {
    Logger::getLogger()->log(INFO, "Relays : Setting up");

    for (size_t i = 0; i < 4; i++)
    {
        pinMode(_relays[i].pin, OUTPUT);
        digitalWrite(_relays[i].pin, _relays[i].state);
        Logger::getLogger()->log(INFO, "Relay " + _relays[i].displayName + " initialized");
    }
}

void RelayHandler::toggleRelay(uint8_t relayIndex) {
    if (relayIndex < 4) {
        _relays[relayIndex].state = (_relays[relayIndex].state == RELAY_ON) ? RELAY_OFF : RELAY_ON;
        digitalWrite(_relays[relayIndex].pin, _relays[relayIndex].state);
        Logger::getLogger()->log(INFO, "Relay " + _relays[relayIndex].displayName + " toggled");
    }
}

Relay RelayHandler::getRelay(uint8_t relayIndex) {
    return _relays[relayIndex];
}
