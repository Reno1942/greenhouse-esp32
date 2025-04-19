#include "SensorHandler.h"

SensorHandler::SensorHandler() :
    _sensorPins{
        .waterLevel = 1,
        .ultrasonicTrig = 12, 
        .ultrasonicEcho = 13, 
        .dht = 0
    },
    _dht(_sensorPins.dht, 11),
    _ultrasonic(_sensorPins.ultrasonicTrig, _sensorPins.ultrasonicEcho)
{}

void SensorHandler::setupDHT() {
    Logger::getLogger()->log(INFO, "DHT: Setting up");
    _dht.begin();
}

void SensorHandler::setupWaterLevel() {
    Logger::getLogger()->log(INFO, "WL Sensor: Setting up");
    pinMode(_sensorPins.waterLevel, INPUT_PULLUP);
}

float SensorHandler::readTemperature() {
    sensors_event_t event;
    _dht.temperature().getEvent(&event);
    return event.temperature;
}

float SensorHandler::readHumidity() {
    sensors_event_t event;
    _dht.humidity().getEvent(&event);
    return event.relative_humidity;
}

int SensorHandler::readTankPercentage() {
    int distanceCM = _ultrasonic.read();
    int tankLevelPercentage = 0;

    if (distanceCM <= _minWaterDistance) {
        tankLevelPercentage = 100;
    }
    else if (distanceCM <= _maxWaterDistance) {
        tankLevelPercentage = ((_maxWaterDistance - distanceCM) / (float)(_maxWaterDistance - _minWaterDistance)) * 100;
    }

    return tankLevelPercentage;
}

bool SensorHandler::wlSensorReached() {
    return digitalRead(_sensorPins.waterLevel) == HIGH;
}