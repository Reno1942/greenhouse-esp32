#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <Logger.h>

enum RelayState : uint8_t {
    RELAY_OFF = 1,
    RELAY_ON = 0    
};

struct Relay {
    String displayName;
    uint8_t pin;
    RelayState state;
};

class RelayHandler {
private:
    Relay _relays[4];

public:    
    RelayHandler();

    void setupRelays();
    void toggleRelay(uint8_t relayIndex);
    Relay getRelay(uint8_t relayIndex);    
};

#endif