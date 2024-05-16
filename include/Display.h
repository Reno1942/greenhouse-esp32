#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "PinsDefinitions.h"
#include "Relay.h"
#include "Sensors.h"

struct LCDValues
{
    const int address = 0x27;
    const byte cols = 20;
    const byte rows = 4;    
};

enum Page
{
    HOME_PAGE,
    RELAYS_PAGE,
    SETTINGS_PAGE,
    PAGE_COUNT
};

extern int tankLevelPercentage;
extern bool autoMode;
extern RelayState relayState[4];

extern int lightOnTime;
extern int lightOffTime;
extern int currentCursorY;

extern float currentTemp;
extern float currentHumidity;

void setupLCD();
void displayHomePage();
void displayRelaysPage();
void displaySettingsPage();
void clearRow(int row);
void clearScreen();
void updateCursor();

#endif