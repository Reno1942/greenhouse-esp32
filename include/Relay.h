#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "PinsDefinitions.h"

/**
 * @brief Enumeration representing the state of a relay.
 */
enum RelayState : byte 
{
    RELAY_OFF = 1,  /** < Relay is off */
    RELAY_ON = 0,   /** < Relay is on */
    RELAY_INIT = 2  /** < Relay is being initialized */
};

/**
 * @brief Enumeration representing the index of a relay.
 */
enum RelayIndex {    
    TopL,   /** < Top light relay */
    BtmL,   /** < Bottom light relay */
    Fan,    /** < Fan relay */
    Pump    /** < Pump relay */
};

extern RelaysPins relaysPins; /** < External declaration of the RelayPins object. */

/**
 * @brief Function pointer type for relay toggle functions.
 */
typedef void (*FunctionPointer)();

/**
 * @brief Sets up the relays.
 */
void setupRelays();

/**
 * @brief Toggles a relay based on the relay pin and relay index.
 * 
 * @param relayPin The pin number of the relay.
 * @param relayIndex The index of the relay.
 */
void toggleRelay(byte relayPin, RelayIndex relayIndex);

/**
 * @brief Checks if a relay is currently on.
 * 
 * @param relayPin The pin number of the relay.
 * @return True if the relay is on, false otherwise.
 */
bool isRelayOn(byte relayPin);

/**
 * @brief Toggles the top light relay.
 */
void toggleTopLight();

/**
 * @brief Toggles the bottom light relay.
 */
void toggleBottomLight();

/**
 * @brief Toggles the fan relay.
 */
void toggleFan();

/**
 * @brief Toggles the pump relay.
 */
void togglePump();

#endif