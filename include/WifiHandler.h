#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include "Credentials.h"
#include "Logger.h"

class WifiHandler {
private:

public:
    WifiHandler();
    bool connectWifi();
};

#endif