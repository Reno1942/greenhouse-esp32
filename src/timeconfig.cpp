#include <Arduino.h>
#include "TimeConfig.h"

bool updateTime() {  
    const int retryIntervalMs = 500;
    const int maxRetries = 10;    

    for (int i = 0; i < maxRetries; i++)
    {
        if (getLocalTime(&timeinfo, 1000)) {
            Serial.print("Updated time : ");
            Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
            return true;
        } else {
            Serial.println("Failed to update time, retrying...");
            delay(retryIntervalMs);
        }
    }

    Serial.println("Failed to update time after multiple tries.");
    return false;
}