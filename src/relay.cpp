#include "Relay.h"

// Initial states of the relays
RelayState relayState[4] = { RELAY_OFF, RELAY_OFF, RELAY_OFF, RELAY_ON };

void setupRelays() {
    pinMode(relaysPins.topLight, OUTPUT);
    pinMode(relaysPins.bottomLight, OUTPUT);
    pinMode(relaysPins.pump, OUTPUT);
    pinMode(relaysPins.fan, OUTPUT);

    toggleRelay(relaysPins.topLight, TopL, RELAY_OFF);
    toggleRelay(relaysPins.bottomLight, BtmL, RELAY_OFF);
    toggleRelay(relaysPins.pump, Pump, RELAY_ON);
    toggleRelay(relaysPins.fan, Fan, RELAY_OFF);    
}

void toggleRelay(byte relayPin, RelayIndex relayIndex, RelayState desiredState) {    
    RelayState state;
    if (desiredState == RELAY_INIT) {
        state = static_cast<RelayState>(digitalRead(relayPin));    
        state = (state == RELAY_ON) ? RELAY_OFF : RELAY_ON;
    } else {
        state = desiredState;
    }           
    digitalWrite(relayPin, state);    
    relayState[relayIndex] = state;
    
    const char* stateStr = (state == RELAY_ON ? "ON" : "OFF");    
}

bool isRelayOn(byte relayPin){
    return digitalRead(relayPin) == RELAY_ON;    
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