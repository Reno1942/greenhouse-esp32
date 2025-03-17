#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <Logger.h>

enum RelayState : uint8_t {
    RELAY_OFF = 1,
    RELAY_ON = 0,
    RELAY_INIT = 2
};

struct RelayPins {
    uint8_t topLight;
    uint8_t bottomLight;
    uint8_t fan;
    uint8_t pump;    
};

class RelayHandler {
private:
    RelayPins _relayPins;

public:    
    RelayHandler();

    void setupRelays();
    void toggleRelay(uint8_t);
};

#endif