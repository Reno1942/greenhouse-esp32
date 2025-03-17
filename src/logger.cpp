#include "Logger.h"

Logger* Logger::_instance = nullptr;

Logger::Logger() {
    _destination = TERMINAL;
    _enabled = true;
    _includeTimestamp = true;
}

Logger* Logger::getLogger() {
    if (_instance == nullptr) {
        _instance = new Logger();
    }
    return _instance;    
}

void Logger::enable() {
    _enabled = true;
}

void Logger::disable() {
    _enabled = false;
}

void Logger::setIncludeTimestamp(bool include) {
    _includeTimestamp = include;
}

String Logger::getTimestamp() {
    // TODO get back to this, millis log time since arduino started, when it should log the actual timestamp
    unsigned long currentMillis = millis();

    unsigned long seconds = currentMillis / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;

    String timestamp = "";

    if (hours < 10) timestamp += "0";
    timestamp += String(hours) + ":";

    if ((minutes % 60) < 10) timestamp += "0";
    timestamp += String(minutes % 60) + ":";
    
    if ((seconds % 60) < 10) timestamp += "0";
    timestamp += String(seconds % 60);

    return timestamp;
}

void Logger::setDestination(LogDestination destination) {
    _destination = destination;
}

void Logger::log(LogLevel level, const String& message) {
    if (!_enabled) return;

    String logMessage = "";

    if (_includeTimestamp) {
        logMessage += "[" + getTimestamp() + "] ";
    }

    switch (level)
    {
        case DEBUG:
            logMessage += "[DEBUG] ";
            break;
        case INFO:
            logMessage += "[INFO] ";
            break;
        case WARNING:
            logMessage += "[WARNING] ";
            break;
        case ERROR:
            logMessage += "[ERROR] ";
            break;
        default:
            logMessage += "[INFO] ";
            break;
    }

    logMessage += message;

    if (_destination == TERMINAL || _destination == BOTH)
    {
        Serial.println(logMessage);
    }

    if (_destination == SD_CARD || _destination == BOTH) {
        // future sd card logging implementation
    }
}