#include <Arduino.h>

#include "SDHandler.h"
#include "Display.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "WifiHandler.h"
#include "TimeHandler.h"
#include "Joystick.h"

// objects
SDHandler sdHandler;
Display display;
RelayHandler relayHandler;
Settings settings;
SensorHandler sensorHandler;
WifiHandler wifiHandler;
TimeHandler timeHandler;
Joystick joystick;

// global variables
bool wifiConnected;

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
    joystick.setup();

    // connect to wifi
    wifiConnected = wifiHandler.connectWifi();

    // // sync time
    // if (wifiConnected) {
        
    // }
    // connect mqtt
}

void loop() {    
    Serial.println("Looping...");
    delay(1000);
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