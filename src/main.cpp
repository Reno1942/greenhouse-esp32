#include <Arduino.h>

#include "SDHandler.h"
#include "Display.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "WifiHandler.h"
#include "TimeHandler.h"

// objects
SDHandler sdHandler;
Display display;
RelayHandler relayHandler;
Settings settings;
SensorHandler sensorHandler;
WifiHandler wifiHandler;
TimeHandler timeHandler;

// global variables
struct tm currentTime;
bool wifiConnected;
bool mqttConnected;

void setup() {
    Serial.begin(115200);
    
    // CURRENTLY NOT WORKING
    // read settings from sd    
    // sdHandler.setupSDCard();    
    // sdHandler.loadSettings(settings);

    // start physical components
    display.setup();
    relayHandler.setupRelays();
    sensorHandler.setupDHT();
    sensorHandler.setupWaterLevel();
    sensorHandler.setupUltrasonic();

    // connect to wifi
    wifiConnected = wifiHandler.connectWifi();

    // sync time
    if (wifiConnected) {
        timeHandler.syncTime(&currentTime);
    }
    // connect mqtt
}

void loop() {
    // CONTROLS
    // handle joystick controls    

    // run automode    

    // SAFEGUARDS 
    // gutter water level
    // tank water level

    // UPDATES
    // update sensors readings    

    // sync the time

    // COMMUNICATION
    // send mqtt states
    // handle mqtt commands
}