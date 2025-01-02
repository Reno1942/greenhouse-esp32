#ifndef AUTO_MODE_H
#define AUTO_MODE_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Relay.h"

extern int lightOnTime;
extern int lightOffTime;
extern float currentTemp;
extern float currentHumidity;
extern struct tm timeinfo;
extern bool autoMode;

void toggleAutoMode();

void runAutoMode();

void checkAndToggleLights(byte pin, RelayIndex relayIndex);

void checkAndToggleFan(byte pin, RelayIndex relayIndex);

#endif