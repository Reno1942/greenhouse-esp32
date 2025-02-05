#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "PinsDefinitions.h"

enum RelayState : byte 
{
    RELAY_OFF = 1,
    RELAY_ON = 0,
    RELAY_INIT = 2
};

enum RelayIndex {    
    TopL,
    BtmL,
    Fan,
    Pump
};

extern RelaysPins relaysPins;

typedef void (*FunctionPointer)();

void setupRelays();

void toggleRelay(byte relayPin, RelayIndex relayIndex, RelayState desiredState = RELAY_INIT);

bool isRelayOn(byte relayPin);

void toggleTopLight();

void toggleBottomLight();

void toggleFan();

void togglePump();

#endif