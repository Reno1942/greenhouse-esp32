#ifndef GREENHOUSE_ESP32_WIFICONTROLLER_H
#define GREENHOUSE_ESP32_WIFICONTROLLER_H

#include <WiFi.h>
#include "Credentials.h"

class WiFiController {
public:
    WiFiController();

    void setup();

    void setupTime();

    bool getUsingRealTime();

private:
    bool usingRealTime = false;
};

#endif //GREENHOUSE_ESP32_WIFICONTROLLER_H