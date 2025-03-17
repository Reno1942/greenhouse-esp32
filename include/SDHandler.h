#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Logger.h>
#include <ArduinoJson.h>

struct SDPins {
    uint8_t cs;
    uint8_t miso;
    uint8_t mosi;
    uint8_t sck;
};

struct Settings {
    uint8_t lightOnTime;
    uint8_t lightOffTime;
};

class SDHandler {
private:
    SDPins _sdPins;    
    char* settingsFilePath;
    char* logsFilePath;    
public:
    SDHandler();

    bool setupSDCard();
    String loadSettings(Settings& settings);
    bool saveSettings(const Settings& settings);
    bool writeLog(String message);    
};

#endif