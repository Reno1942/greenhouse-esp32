#include <Arduino.h>

#include "SDHandler.h"
#include "Display.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "WifiHandler.h"

SDHandler sdHandler;
Display display;
RelayHandler relayHandler;
Settings settings;
SensorHandler sensorHandler;
WifiHandler wifiHandler;

void setup() {
    Serial.begin(115200);
    
    // read settings from sd    
    sdHandler.setupSDCard();
    sdHandler.loadSettings(settings);

    // start physical components
    display.setup();
    relayHandler.setupRelays();
    sensorHandler.setupDHT();
    sensorHandler.setupWaterLevel();
    sensorHandler.setupUltrasonic();

    // connect to wifi
    wifiHandler.connectWifi();

    // sync time

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