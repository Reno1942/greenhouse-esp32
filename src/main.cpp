#include <Arduino.h>
#include <Wire.h> 

#include "PinsDefinitions.h"
#include "Display.h"
#include "Joystick.h"
#include "Sensors.h"
#include "Relay.h"
#include "WiFiConfig.h"
#include "TimeConfig.h"

// Struct storing the pin number of the relays
RelaysPins relaysPins;

// Struct storing the pin number of the sensors
SensorsPins sensorsPins;

// Struct storing the pin number of the joystick
JoystickPins joystickPins;

bool autoMode = true;

// struct storing the time for displaying
struct tm timeinfo;

// address of the ntp server used to synchronize the time
const char* ntpServer = "pool.ntp.org";

// offset of the current timezone compared to gmt
const long gmtOffset_sec = -18000;

// daylight savings offset
const int daylightOffset_sec = 3600;

// hour chosen to turn on lights
int lightOnTime = 6;

// hour chosen to turn off lights
int lightOffTime = 0;

// Current temperature read by the DHT sensor
float currentTemp = -1;

// Current humidity read by the DHT sensor
float currentHumidity = -1;

// Percentage of the water tank's fill level
int tankLevelPercentage = -1;

// Milliseconds since the program started
unsigned long now = 0;

// Timestamp of the last sensor update
unsigned long lastSensorUpdate = 0;

// Delay between sensor updates in milliseconds
const unsigned long sensorUpdateDelay = 1000;

// Timestamp of the last time the pump was turned off
unsigned long lastPumpOffTime = 0;

// Delay before the pump can be turned on again in milliseconds
const unsigned long pumpOffDelay = 60000;

// Timestamp of the last time the timeinfo was synced with NTP
unsigned long lastNtpSync = 0;

// Delay between NTP syncs in milliseconds
const unsigned long ntpSyncDelay = 3600000;

void setup() {
    // init serial comm
    Serial.begin(115200);

    // print the reason for the esp reset
    esp_reset_reason_t reason = esp_reset_reason();    
    Serial.print("Reset reason: ");
    Serial.println(reason);

    // setup the components
    connectWifi();    
    setupRelays();
    setupLCD();
    setupJoystick();    
    setupDHT();    
    setupWaterLevelSensor();    

    // config the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    updateTime();    
    Serial.println("Setup done");
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
        updateTankLevelPercentage();        
        lastSensorUpdate = now;
    }

    // sync time with ntp
    if (now - lastNtpSync >= ntpSyncDelay) {
        updateTime();
        lastNtpSync = now;
    }

    // run automode
    if (autoMode) runAutoMode();
    
    bool isTankEmptyAndPumpOn = tankLevelPercentage == 0 && isRelayOn(relaysPins.pump);
    bool isTankOkAndPumpOff = tankLevelPercentage > 5 && !isRelayOn(relaysPins.pump);
    bool isDelayPassed = now - lastPumpOffTime >= pumpOffDelay;

    // toggle pump depending on water fill and delay
    if (isTankEmptyAndPumpOn || (isTankOkAndPumpOff && autoMode && isDelayPassed)) {
        togglePump();
    }

    // turn off the pump if water level sensor is reached and keep it off for a delay
    if (isSensorReached() && isRelayOn(relaysPins.pump)) {
        togglePump();
        lastPumpOffTime = now;
    }
}