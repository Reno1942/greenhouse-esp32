#include "WifiHandler.h"

WifiHandler::WifiHandler()
{}

bool WifiHandler::connectWifi() {
    const unsigned long wifiTimeout = 30000;
    unsigned long startTime = millis();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Logger::getLogger()->log(INFO, "Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startTime >= wifiTimeout) {
            Logger::getLogger()->log(ERROR, "WiFi connection failed");
            return false;
        }

        delay(500);
    }

    Logger::getLogger()->log(INFO, "Connected to WiFi");
    return true;
    
}