#include "WiFiConfig.h"

void setupWifi() {
    const unsigned long wifiTimeout = 30000;
    unsigned long startTime = millis();

    WiFi.begin(WIFI_SSID, WIFI_PWD);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startTime >= wifiTimeout) {
            Serial.println("WiFi connection failed");
            return;
        }

        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi");
}