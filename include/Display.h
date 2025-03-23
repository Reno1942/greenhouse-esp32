#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "Logger.h"

// Struct to hold LCD configuration values
struct LCDValues {
    int address;
    uint8_t cols;  
    uint8_t rows;    
};

// Struct to hold LCD pin configuration
struct LCDPins {
    uint8_t sda;     
    uint8_t scl;
};

class Display {
private:
    LCDValues _lcdValues;
    LCDPins _lcdPins;
    hd44780_I2Cexp _lcd;

public:
    Display();

    bool setup();
    void clearRow(int row);
    void clearScreen();
};

#endif