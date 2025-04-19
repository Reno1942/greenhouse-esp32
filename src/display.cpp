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

void Display::displayHomePage(bool refresh) {    
    // temp and humidity
    if (_previousHumidity != _displayData.humidity || _previousTemperature != _displayData.temperature || refresh) {
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
    if (_previousTankPercentage != _displayData.tankLevelPercentage || refresh) {
        clearRow(2);
        _lcd.setCursor(4,2);
        _lcd.print("Tank : ");
        _lcd.print(_displayData.tankLevelPercentage);
        _lcd.print("%");

        _previousTankPercentage = _displayData.tankLevelPercentage;
    }
    

    // mode    
    if (_previousAutomode != _displayData.isAutoModeOn || refresh) {
        clearRow(3);
        _lcd.setCursor(0,3);
        _lcd.print(_displayData.isAutoModeOn ? "X   Mode : Auto" : "X   Mode : Manual");

        _previousAutomode = _displayData.isAutoModeOn;
    }
    
    resetCursor();
}


void Display::displayRelaysPage(bool refresh) {    
    for (size_t i = 0; i < 4; i++)
    {            
        if (_previousRelays[i].state != _displayData.relays[i].state || refresh) {            
            clearRow(i);
            _lcd.setCursor(0, i);
            _lcd.print(_displayData.relays[i].displayName);
            _lcd.setCursor(9, i);
            _lcd.print(": ");
            _lcd.print(_displayData.relays[i].state == RELAY_ON ? "ON" : "OFF");
            _previousRelays[i].state = _displayData.relays[i].state;            
        }            
    } 
    resetCursor();
}

void Display::displaySettingsPage(bool refresh) {     
    _lcd.setCursor(0, 0);
    _lcd.print("Settings");
    resetCursor();
}

void Display::changePage(bool next) {
    clearScreen();
    
    if (next) {
        _currentPage = static_cast<Page>((_currentPage + 1) % PAGE_COUNT);
        Serial.println(_currentPage);
        _currentCursorY = 0;
    } else {
        _currentPage = (_currentPage == HOME_PAGE) ? SETTINGS_PAGE : static_cast<Page>(_currentPage - 1);
        Serial.println(_currentPage);
        _currentCursorY = 3;
    }
    
    switch (_currentPage) {
        case HOME_PAGE:
            displayHomePage(true);
            break;
        case RELAYS_PAGE:
            displayRelaysPage(true);
            break;
        case SETTINGS_PAGE:
            displaySettingsPage(true);
            break;
    }
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