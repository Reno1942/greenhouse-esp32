#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "PinsDefinitions.h"

struct LCDValues
{
    const int address = 0x27;
    const byte cols = 20;
    const byte rows = 4;    
};

extern bool tankNeedsRefill;
extern bool autoMode;
extern bool relayState[4];

void setupLCD();
void displayHomePage();
void displayRelaysPage();
void clearRow(int row);


#endif