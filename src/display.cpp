#include "Display.h"

Display::Display() :
    _lcdValues{
        .address = 0x27,
        .cols = 20,
        .rows = 4
    },
    _lcdPins{
        .sda = 10,
        .scl = 11
    },
    _lcd(_lcdValues.address)
{}

bool Display::setup() {
    bool wireInitStatus = Wire.begin(_lcdPins.sda, _lcdPins.scl);
    if (!wireInitStatus) {
        Logger::getLogger()->log(ERROR, "LCD: Wire did not initialize correctly");
        return false;
    }
    Logger::getLogger()->log(INFO, "LCD: Wire initialized successfully");

    int lcdInitStatus = _lcd.begin(_lcdValues.cols, _lcdValues.rows);
    if (lcdInitStatus == 0) {
        Logger::getLogger()->log(INFO, "LCD: Setting up");        
        _lcd.backlight();
        _lcd.blink();
        Logger::getLogger()->log(INFO, "LCD: Initialized successfully");        
        return true;
    }

    Logger::getLogger()->log(ERROR, "LCD: Did not initialize correctly");
    return false;
}

void Display::clearRow(int row) {
    for (size_t i = 0; i < _lcdValues.cols; i++)
    {
        _lcd.setCursor(i, row);
        _lcd.print(" ");
    }    
}

void Display::clearScreen() {
    for (size_t i = 0; i < _lcdValues.rows; i++)
    {
        clearRow(i);
    }    
}