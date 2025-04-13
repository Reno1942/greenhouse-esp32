#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include <WiFi.h>
#include "Logger.h"

class TimeHandler {
private:
    const char* ntpServer;
    const long gmtOffset;
    const int daylightOffset;

public:
    TimeHandler();
    bool syncTime(tm *timeinfo);        
};

#endif