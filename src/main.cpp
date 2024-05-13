// libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <Ultrasonic.h>

// local includes
#include "PinsDefinitions.h"
#include "Display.h"
#include "Joystick.h"
#include "Relay.h"
#include "WiFiConfig.h"
#include "Credentials.h"
#include "TimeConfig.h"

// pins structs
SensorsPins sensorsPins;

// time & ntp
struct tm timeinfo;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -14400;
const int daylightOffset_sec = 0;

// objects creation
DHT_Unified dht(sensorsPins.dht, 11);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);

// light time settings
int lightOnTime = 6;
int lightOffTime = 0;

// other variables
const float minimumWaterDistance = 100.0;
bool tankNeedsRefill = false;
bool autoMode = false;


// function declarations
void setupJoystick();
void setupWifi();
void updateTimeTask(void * parameter);

void setup() {
    Serial.begin(115200);  

    setupRelays();
    setupLCD();
    setupJoystick();
    setupWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);   
    xTaskCreate(updateTimeTask, "Update Time", 10000, NULL, 1, NULL); 
}

void loop() {    
    handleJoystickControl();
    handleJoystickClick();
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

void setLightOnTime(int newValue) {
    lightOnTime = newValue;
}

void setLightOffTime(int newValue) {
    lightOffTime = newValue;
}