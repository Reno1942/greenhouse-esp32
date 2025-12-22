#ifndef GREENHOUSE_ESP32_RELAYHANDLER_H
#define GREENHOUSE_ESP32_RELAYHANDLER_H

#include <Arduino.h>

enum RelayState : uint8_t {
    RELAY_OFF = 1,
    RELAY_ON = 0,
};

struct Relay {
    uint8_t pin;
    RelayState state;
};

using RelayEntry = std::pair<const char*, Relay>;

class RelayController {
public:
    RelayController();

    void setupRelays();
    void toggleRelay(const char* relayName);
    std::array<RelayEntry, 4>& getRelays();

private:
    std::array<RelayEntry, 4> relays;
};

#endif //GREENHOUSE_ESP32_RELAYHANDLER_H