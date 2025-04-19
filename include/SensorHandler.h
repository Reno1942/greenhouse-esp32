#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Ultrasonic.h>
#include "Logger.h"

struct SensorsPins {
    uint8_t waterLevel;
    uint8_t ultrasonicTrig;
    uint8_t ultrasonicEcho;
    uint8_t dht;
};

class SensorHandler {
private:
    SensorsPins _sensorPins;    
    DHT_Unified _dht; 
    Ultrasonic _ultrasonic;

    const int _minWaterDistance = 5;
    const int _maxWaterDistance = 30;
public:
    SensorHandler();

    void setupWaterLevel();    
    void setupDHT();
    float readTemperature();
    float readHumidity();
    bool wlSensorReached();
    int readTankPercentage();
};

#endif