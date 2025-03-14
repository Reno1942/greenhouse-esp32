#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogDestination {
    TERMINAL,
    SD_CARD,
    BOTH
};

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    Logger();
    static Logger* _instance;

    LogDestination _destination;
    bool _enabled;
    bool _includeTimestamp;

public:    
    static Logger* getLogger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void enable();
    void disable();    
    void setDestination(LogDestination destination);    
    void setIncludeTimestamp(bool include);

    void log(LogLevel level, const String& message);
    String getTimestamp();    
};

#endif