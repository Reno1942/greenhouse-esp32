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
#include "WiFiConfig.h"
#include "Credentials.h"
#include "TimeConfig.h"

// pins structs
RelaysPins relaysPins;
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
RelayState relayState[4] = { RELAY_OFF, RELAY_OFF, RELAY_OFF, RELAY_OFF };

// function declarations
void setupJoystick();
void setupRelays();
void setupWifi();

void toggleRelay(byte relayPin, RelayIndex relayIndex);
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
}

// function definitions
void setupWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi");
}

void setupRelays() {
    pinMode(relaysPins.topLight, OUTPUT);
    pinMode(relaysPins.bottomLight, OUTPUT);
    pinMode(relaysPins.pump, OUTPUT);
    pinMode(relaysPins.fan, OUTPUT);

    digitalWrite(relaysPins.topLight, RELAY_OFF);
    digitalWrite(relaysPins.bottomLight, RELAY_OFF);
    digitalWrite(relaysPins.pump, RELAY_OFF);
    digitalWrite(relaysPins.fan, RELAY_OFF);
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

void toggleRelay(byte relayPin, RelayIndex relayIndex) {
    RelayState state = static_cast<RelayState>(digitalRead(relayPin));    
    if (state == RELAY_ON) state = RELAY_OFF;        
    else if (state == RELAY_OFF) state = RELAY_ON;    
    digitalWrite(relayPin, state);    
    relayState[relayIndex] = state;
}

void setLightOnTime(int newValue) {
    lightOnTime = newValue;
}

void setLightOffTime(int newValue) {
    lightOffTime = newValue;
}