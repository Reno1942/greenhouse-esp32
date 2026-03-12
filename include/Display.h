#ifndef GREENHOUSE_ESP32_DISPLAY_H
#define GREENHOUSE_ESP32_DISPLAY_H

#include <Wire.h>
#include <map>
#include <string>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "ModeController.h"
#include "RelayController.h"
#include "SensorController.h"

struct LCDValues {
    int address;
    uint8_t cols;
    uint8_t rows;
};

struct LCDPins {
    uint8_t sda;
    uint8_t scl;
};

struct DisplayData {
    float displayedTemperature;
    float displayedHumidity;
    int displayedTankPercentage;
    AutoModeState displayedAutoModeState;
    uint8_t displayedMinute;

    std::map<std::string, RelayState> displayedRelayStates;
};

enum CursorMoveDirection {
    DOWN,
    UP
};

class Display {
public:
    Display(RelayController &_relayController, ModeController &_modeController, SensorController &_sensorController, RTC_DS1307 &_rtc);

    bool setup();

    void displayRelays();

    void displaySensors();

    void displayAutoMode();

    void displayDateTime();

    int getCursorPosition();

    void moveCursor(CursorMoveDirection direction);

    void watchSleepMode();

private:
    DisplayData displayData;
    LCDValues lcdValues;
    LCDPins lcdPins;
    hd44780_I2Cexp lcd;

    RelayController &relayController;
    SensorController &sensorController;
    ModeController &modeController;
    RTC_DS1307 &rtc;

    void wakeDisplay();

    void resetCursor();

    int cursorPosition = 0;
    unsigned long lastCursorMoveTime = 0;
    const unsigned long displaySleepTime = 300000;
    bool displaySleeping = false;
};

#endif //GREENHOUSE_ESP32_DISPLAY_H
