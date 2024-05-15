#include "AutoMode.h"

bool fanOn = false;

void toggleAutoMode() {
    autoMode = !autoMode; 
}

void runAutoMode() {
    checkAndToggleLights(relaysPins.topLight, TopL);
    checkAndToggleLights(relaysPins.bottomLight, BtmL);
    checkAndToggleFan(relaysPins.fan, Fan); 
}

void checkAndToggleLights(byte pin, RelayIndex relayIndex) {    
    bool lightsOn = timeinfo.tm_hour < lightOffTime || timeinfo.tm_hour >= lightOnTime;    

    if (lightsOn != isRelayOn(pin)) {
        toggleRelay(pin, relayIndex);
    }
}

void checkAndToggleFan(byte pin, RelayIndex relayIndex) {
    if (currentHumidity >= 75.0) {
        fanOn = true;
    } else if (currentHumidity <= 65.0) {
        fanOn = false;
    }    

    if (fanOn != isRelayOn(pin)) {
        toggleRelay(pin, relayIndex);
    }
}