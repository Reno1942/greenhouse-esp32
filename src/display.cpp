#include "Display.h"

Display::Display(DisplayData& displayData) :
    _lcdValues{.address = 0x27, .cols = 20, .rows = 4},
    _lcdPins{.sda = 10, .scl = 11},
    _lcd(_lcdValues.address),
    _currentCursorY(0),
    _displayData(displayData)    
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
        displayHomePage();
        Logger::getLogger()->log(INFO, "LCD: Initialized successfully");                
        return true;
    }

    Logger::getLogger()->log(ERROR, "LCD: Did not initialize correctly");
    return false;
}

void Display::setCurrentCursorY(uint8_t newCursorY) {        
    _currentCursorY = newCursorY;
    _lcd.setCursor(0, _currentCursorY);
}

uint8_t Display::getCurrentCursorY() {
    return _currentCursorY;
}

void Display::displayHomePage() {    
    // temp and humidity
    if (_previousHumidity != _displayData.humidity || _previousTemperature != _displayData.temperature) {
        clearRow(0);
        _lcd.setCursor(0,0);
        _lcd.print("Temp:");    
        _lcd.print(_displayData.temperature, 1);
        _lcd.print("C Hum:");
        _lcd.print(_displayData.humidity, 1);
        _lcd.print("%");

        _previousTemperature = _displayData.temperature;
        _previousHumidity = _displayData.humidity;
    }

    // tank level
    if (_previousTankPercentage != _displayData.tankLevelPercentage) {
        clearRow(2);
        _lcd.setCursor(4,2);
        _lcd.print("Tank : ");
        _lcd.print(_displayData.tankLevelPercentage);
        _lcd.print("%");

        _previousTankPercentage = _displayData.tankLevelPercentage;
    }
    

    // mode    
    if (_previousAutomode != _displayData.autoMode) {
        clearRow(3);
        _lcd.setCursor(0,3);
        _lcd.print(_displayData.autoMode ? "X   Mode : Auto" : "X   Mode : Manual");

        _previousAutomode = _displayData.autoMode;
    }
    
    resetCursor();
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

void Display::resetCursor() {
    _lcd.setCursor(0, _currentCursorY);
}

Page Display::getCurrentPage() {
    return _currentPage;
}