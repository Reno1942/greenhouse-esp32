#include "SDHandler.h"

SDHandler::SDHandler() :
    _sdPins{
        .cs = 18,
        .miso = 7, 
        .mosi = 2, 
        .sck = 6
    },    
    settingsFilePath("/appsettings.txt"),
    logsFilePath("/logs/testLog.txt")
{}

bool SDHandler::setupSDCard() {    
    Logger::getLogger()->log(INFO, "SD: Setting up");
    SPIClass spi = SPIClass(FSPI);
    spi.begin(_sdPins.sck, _sdPins.miso, _sdPins.mosi, _sdPins.cs);

    if (!SD.begin(_sdPins.cs, spi)) {
        Logger::getLogger()->log(ERROR, "SD: Card mount failed.");
        return false;
    }        

    Logger::getLogger()->log(INFO, "SD: Initialized successfully");
    return true;
}

void SDHandler::loadSettings(Settings& settings) {
    // TODO: Fix this, Core panics when trying to open file.
    Logger::getLogger()->log(INFO, "SD: Opening settings file");
    File settingsFile = SD.open(settingsFilePath);
    
    if (!settingsFile) {
        Logger::getLogger()->log(ERROR, "SD: Failed to open file");
    }
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, settingsFile);
    if (error) Logger::getLogger()->log(ERROR, "SD: Failed to read file");

    settings.lightOnTime = doc["lightOnTime"] | 6;
    settings.lightOffTime = doc["lightOffTime"] | 0;

    settingsFile.close();
    Logger::getLogger()->log(INFO, "SD: Settings loaded successfully");
}

bool SDHandler::saveSettings(const Settings& settings) {
    if (!SD.remove(settingsFilePath)) {
        Logger::getLogger()->log(ERROR, "SD: Failed to delete settings file.");
        return false;
    }
    
    File settingsFile = SD.open(settingsFilePath, FILE_WRITE);
    if (!settingsFile) {
        Logger::getLogger()->log(ERROR, "SD: Failed to create settings file.");
        return false;
    }

    //TODO: implement saving
    return true;
}

bool SDHandler::writeLog(String message) {
    // TODO: Implement log writing
    return false;
}