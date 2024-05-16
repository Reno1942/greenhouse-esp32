#ifndef AUTO_MODE_H
#define AUTO_MODE_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Relay.h"

extern int lightOnTime; /**< External declaration of the time when the lights should be turned on. */
extern int lightOffTime; /**< External declaration of the time when the lights should be turned off. */
extern float currentTemp; /**< External declaration of the current temperature. */
extern float currentHumidity; /**< External declaration of the current humidity. */
extern struct tm timeinfo; /**< External declaration of the current time. */
extern bool autoMode; /**< External declaration of whether the auto mode is enabled or not. */

/**
 * @brief Toggles the auto mode on or off.
 */
void toggleAutoMode();

/**
 * @brief Runs the automatic mode in the loop.
 */
void runAutoMode();

/**
 * @brief Check if the light should be toggled and toggles it if needed.
 * 
 * @param pin The pin number of the relay to check.
 * @param relayIndex The index of the relay to toggle.
 * 
 */
void checkAndToggleLights(byte pin, RelayIndex relayIndex);

/**
 * @brief Check if the fan should be toggled and toggles it if needed.
 * 
 * @param pin The pin number of the relay to check.
 * @param relayIndex The index of the relay to toggle.
 * 
 */
void checkAndToggleFan(byte pin, RelayIndex relayIndex);

#endif