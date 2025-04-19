#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "Logger.h"
#include "SensorHandler.h"
#include "DisplayData.h"

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

// Enum containing the different pages of the display
enum Page {
    HOME_PAGE,
    RELAYS_PAGE,
    SETTINGS_PAGE,
    PAGE_COUNT
};

class Display {
private:
    LCDValues _lcdValues;
    LCDPins _lcdPins;
    hd44780_I2Cexp _lcd;
    uint8_t _currentCursorY;
    DisplayData& _displayData;

    float _previousTemperature = 0;
    float _previousHumidity = 0;
    int _previousTankPercentage = 0;
    bool _previousAutomode = false;
    Page _currentPage = HOME_PAGE;
    
public:
    Display(DisplayData& displayData);

    bool setup();
    void clearRow(int row);
    void clearScreen();
    uint8_t getCurrentCursorY();
    void setCurrentCursorY(uint8_t newCursorY);
    void displayHomePage();
    void resetCursor();
    Page getCurrentPage();    
};

#endif