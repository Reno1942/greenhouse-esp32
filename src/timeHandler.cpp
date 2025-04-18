#include "TimeHandler.h"

TimeHandler::TimeHandler() :
    ntpServer("pool.ntp.org"),
    gmtOffset(-18000),
    daylightOffset(3600)
{
    // this causes an issue where the program will hang on object creation
    // configTime(gmtOffset, daylightOffset, ntpServer);
}

bool TimeHandler::syncTime() {
    return false;
}