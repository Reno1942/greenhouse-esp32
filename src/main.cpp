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

int tankLevel = -1;
bool autoMode = true;

unsigned long now = 0;
unsigned long lastSensorUpdate = 0;
const unsigned long sensorUpdateDelay = 1000;
unsigned long lastPumpOffTime = 0;
const unsigned long pumpOffDelay = 60000;
unsigned long lastTimeUpdate = 0;
const unsigned long timeUpdateDelay = 1000;

void setupWifi();
void updateTimeTask(void * parameter);

void setup() {
    Serial.begin(115200);  
    setupRelays();
    setupLCD();
    setupJoystick();
    setupDHT();
    setupWaterLevelSensor();
    setupWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);       
}

void loop() {  
    // update current millis
    now = millis();

    // handle joystick 
    handleJoystickControl();
    handleJoystickClick();

    // update dht and ultrasonic readings
    if (now - lastSensorUpdate >= sensorUpdateDelay) {
        updateDhtReadings();
        updateTankLevel();
        lastSensorUpdate = now;
    }

    // update time
    if (now - lastTimeUpdate >= timeUpdateDelay) {
        getLocalTime(&timeinfo, 1000);
    }

    // run automode
    if (autoMode) runAutoMode();
    isSensorReached();    

    // turn off the pump if water level is too low
    bool isTankEmptyAndPumpOn = tankLevel == 0 && isRelayOn(relaysPins.pump);
    bool isTankOkAndPumpOff = tankLevel > 5 && !isRelayOn(relaysPins.pump);
    bool isDelayPassed = now - lastPumpOffTime >= pumpOffDelay;
    if (isTankEmptyAndPumpOn || (isTankOkAndPumpOff && autoMode && isDelayPassed)) {
        togglePump();
    }

    // turn off the pump if water level sensor is reached
    if (isSensorReached() && isRelayOn(relaysPins.pump)) {
        togglePump();
        lastPumpOffTime = now;
    }        
}

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