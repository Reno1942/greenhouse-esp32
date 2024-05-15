#include "Relay.h"

RelayState relayState[4] = { RELAY_OFF, RELAY_OFF, RELAY_OFF, RELAY_OFF };

void setupRelays() {
    pinMode(relaysPins.topLight, OUTPUT);
    pinMode(relaysPins.bottomLight, OUTPUT);
    pinMode(relaysPins.pump, OUTPUT);
    pinMode(relaysPins.fan, OUTPUT);

    digitalWrite(relaysPins.topLight, RELAY_OFF);
    digitalWrite(relaysPins.bottomLight, RELAY_OFF);
    digitalWrite(relaysPins.pump, RELAY_OFF);
    digitalWrite(relaysPins.fan, RELAY_OFF);
}

void toggleRelay(byte relayPin, RelayIndex relayIndex) {
    RelayState state = static_cast<RelayState>(digitalRead(relayPin));    
    state = (state == RELAY_ON) ? RELAY_OFF : RELAY_ON;       
    digitalWrite(relayPin, state);    
    relayState[relayIndex] = state;
}

void toggleTopLight() {
    toggleRelay(relaysPins.topLight, TopL);
}

void toggleBottomLight() {
    toggleRelay(relaysPins.bottomLight, BtmL);
}

void toggleFan() {
    toggleRelay(relaysPins.fan, Fan);
}

void togglePump() {
    toggleRelay(relaysPins.pump, Pump);
}

FunctionPointer relayFunctions[] = {
    toggleTopLight,
    toggleBottomLight,
    toggleFan,
    togglePump
};