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

    std::map<std::string, RelayState> displayedRelayStates;
};

enum CursorMoveDirection {
    DOWN,
    UP
};

class Display {
public:
    Display(RelayController &_relayController, ModeController &_modeController, SensorController &_sensorController);

    bool setup();

    void displayRelays();

    void displaySensors();

    void displayAutoMode();

    int getCurrentCursorY();

    void moveCursor(CursorMoveDirection direction);

private:
    DisplayData displayData;
    LCDValues lcdValues;
    LCDPins lcdPins;
    hd44780_I2Cexp lcd;

    RelayController &relayController;
    SensorController &sensorController;
    ModeController &modeController;

    void resetCursor();

    int currentCursorY = 0;
};

#endif //GREENHOUSE_ESP32_DISPLAY_H
