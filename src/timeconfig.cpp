#include <Arduino.h>
#include "TimeConfig.h"

bool updateTime() {
    int maxTries = 10;

    for (int i = 0; i < maxTries; i++)
    {
        if (getLocalTime(&timeinfo, 1000)) {
            Serial.println("Synced time with NTP : ");
            Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
            return true;
        } else {
            Serial.println("Failed to sync time with NTP, retrying...");
        }
    }

    Serial.println("Failed to sync time with NTP after multiple attempts");
    return false;    
}