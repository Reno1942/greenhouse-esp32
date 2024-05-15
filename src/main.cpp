#include <Arduino.h>
#include <Wire.h> 

#include "PinsDefinitions.h"
#include "Display.h"
#include "Joystick.h"
#include "Sensors.h"
#include "Relay.h"
#include "WiFiConfig.h"
#include "Credentials.h"
#include "TimeConfig.h"

RelaysPins relaysPins;
SensorsPins sensorsPins;
JoystickPins joystickPins;

struct tm timeinfo;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -14400;
const int daylightOffset_sec = 0;

int lightOnTime = 6;
int lightOffTime = 0;

float currentTemp = -1;
float currentHumidity = -1;

const float minimumWaterDistance = 100.0;
bool tankNeedsRefill = false;
bool autoMode = false;

unsigned long lastDhtUpdate = 0;
const unsigned long dhtUpdateInterval = 5000;


// function declarations
void setupJoystick();
void setupWifi();
void updateTimeTask(void * parameter);

void setup() {
    Serial.begin(115200);  

    setupRelays();
    setupLCD();
    setupJoystick();
    setupDHT();
    setupWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);   
    xTaskCreate(updateTimeTask, "Update Time", 10000, NULL, 1, NULL); 
}

void loop() {    
    handleJoystickControl();
    handleJoystickClick();

    if (millis() - lastDhtUpdate >= dhtUpdateInterval) {
        updateDhtReadings();
        lastDhtUpdate = millis();
    }
}

// function definitions
void setupWifi() {
    const unsigned long wifiTimeout = 10000;
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



void updateTimeTask(void * parameter) {
    // run as long as task is active
    for(;;) {
        // update timeinfo, block up to 1000ms on this task
        getLocalTime(&timeinfo, 1000);

        //delay 1000ms for other tasks (non blocking, RTOS task)
        delay(1000);
    }
}

void toggleAutoMode() {
    autoMode = !autoMode;

    if (!autoMode) return;

    // manage lights
    if (timeinfo.tm_hour >= lightOffTime && timeinfo.tm_hour < lightOnTime) {
        if (digitalRead(relaysPins.topLight) == RELAY_ON) {
            toggleRelay(relaysPins.topLight, TopL);
        }

        if (digitalRead(relaysPins.bottomLight) == RELAY_ON) {
            toggleRelay(relaysPins.bottomLight, BtmL);
        }
    }

    // manage fan
}