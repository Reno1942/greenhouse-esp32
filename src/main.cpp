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

    // sync time
    // if (wifiConnected) {
        
    // }
    // connect mqtt
}

void loop() {    
    currentTime = millis();
    
    // handle joystick controls    
    joystick.handleJoystickMovement();    

    // display correct page
    switch(display.getCurrentPage()) {
        case HOME_PAGE:
            display.displayHomePage(false);
            break;
        case RELAYS_PAGE:
            display.displayRelaysPage(false);
            break;
        case SETTINGS_PAGE:
            display.displaySettingsPage(false);
            break;
    }

    // update display data
    if (currentTime - lastDisplayDataUpdate > displayDataUpdateDelay) {
        displayData.humidity = sensorHandler.readHumidity();
        displayData.temperature = sensorHandler.readTemperature();        
        displayData.tankLevelPercentage = sensorHandler.readTankPercentage();
        displayData.isAutoModeOn = true;

        for (size_t i = 0; i < 4; i++)
        {
            displayData.relays[i] = relayHandler.getRelay(i);
        }
        
        lastDisplayDataUpdate = currentTime;
    }    

    // run automode    

    // SAFEGUARDS 
    // gutter water level
    // tank water level                

    // sync the time

    // send mqtt states
    // handle mqtt commands
}