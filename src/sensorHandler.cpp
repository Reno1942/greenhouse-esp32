#include "SensorHandler.h"

SensorHandler::SensorHandler() :
    _sensorPins{1, 12, 13, 0},
    _dht(_sensorPins.dht, 11),
    _ultrasonic(_sensorPins.ultrasonicTrig, _sensorPins.ultrasonicEcho)
{}

void SensorHandler::setupDHT() {
    Logger::getLogger()->log(INFO, "Setting up DHT sensor");
    _dht.begin();
}

void SensorHandler::setupWaterLevel() {
    Logger::getLogger()->log(INFO, "Setting up water level sensor");
    pinMode(_sensorPins.waterLevel, INPUT_PULLUP);
}

void SensorHandler::setupUltrasonic() {
    Logger::getLogger()->log(INFO, "Setting up ultrasonic sensor");
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

bool SensorHandler::wlSensorReached() {
    return digitalRead(_sensorPins.waterLevel) == HIGH;
}
