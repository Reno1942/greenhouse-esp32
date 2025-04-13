#include "TimeHandler.h"

TimeHandler::TimeHandler() :
    ntpServer("pool.ntp.org"),
    gmtOffset(-18000),
    daylightOffset(3600)
{
    configTime(gmtOffset, daylightOffset, ntpServer);
}

bool TimeHandler::syncTime(tm *timeinfo) {
    if (!getLocalTime(&timeinfo)) {
        Logger::getLogger()->log(ERROR, "Time: Failed to obtain time");
        return false;
    }
}