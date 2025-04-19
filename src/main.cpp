#include <Arduino.h>

#include "SDHandler.h"
#include "Display.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "WifiHandler.h"
#include "TimeHandler.h"
#include "Joystick.h"
#include "DisplayData.h"

// OBJECTS
SDHandler sdHandler;
DisplayData displayData;
RelayHandler relayHandler;
Settings settings;
SensorHandler sensorHandler;
WifiHandler wifiHandler;
TimeHandler timeHandler;
Display display(displayData);
Joystick joystick(display);

// VARIABLES
bool wifiConnected;
unsigned long currentTime = 0;
unsigned long lastDisplayDataUpdate = 0;
unsigned long displayDataUpdateDelay = 2000; 

void setup() {
    Serial.begin(115200);    
    // CURRENTLY NOT WORKING
    // read settings from sd    
    // sdHandler.setupSDCard();    
    // sdHandler.loadSettings(settings);

    // start physical components    
    relayHandler.setupRelays();
    sensorHandler.setupDHT();
    sensorHandler.setupWaterLevel();    
    display.setup();
    joystick.setup();

    // connect to wifi
    wifiConnected = wifiHandler.connectWifi();

    // // sync time
    // if (wifiConnected) {
        
    // }
    // connect mqtt
}

void loop() {    
    currentTime = millis();

    // CONTROLS
    // handle joystick controls    
    joystick.handleJoystickMovement();    

    // update display data
    if (currentTime - lastDisplayDataUpdate > displayDataUpdateDelay) {
        displayData.humidity = sensorHandler.readHumidity();
        displayData.temperature = sensorHandler.readTemperature();
        displayData.autoMode = true;
        displayData.tankLevelPercentage = sensorHandler.readTankPercentage();
        lastDisplayDataUpdate = currentTime;
    }

    // display correct page
    switch(display.getCurrentPage()) {
        case HOME_PAGE:
            display.displayHomePage();
            break;
    }

    // run automode    

    // SAFEGUARDS 
    // gutter water level
    // tank water level                

    // sync the time

    // send mqtt states
    // handle mqtt commands
}