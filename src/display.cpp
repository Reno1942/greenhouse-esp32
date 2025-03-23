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
    Wire.begin(_lcdPins.sda, _lcdPins.scl);

    int lcdInitStatus = _lcd.begin(_lcdValues.cols, _lcdValues.rows);

    if (lcdInitStatus != 0) {
        Logger::getLogger()->log(INFO, "Setting up display");

        bool wireInitStatus = Wire.begin(_lcdPins.sda, _lcdPins.scl);        
        if (!wireInitStatus) {
            Logger::getLogger()->log(ERROR, "LCD: Wire did not initialize correctly");
            return false;
        }

        int lcdInitStatus = _lcd.begin(_lcdValues.cols, _lcdValues.rows);
        if (lcdInitStatus != 0) {
            Logger::getLogger()->log(ERROR, "LCD did not initialize correctly.");
            return false;
        }
        _lcd.backlight();
        _lcd.blink();        
        return true;
    }

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