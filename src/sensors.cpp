#include "Sensors.h"

DHT_Unified dht(sensorsPins.dht, 11);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);

const int minWaterDistance = 5;
const int maxWaterDistance = 37;

void setupDHT() {
    dht.begin();
    currentTemp = readTemperature();
    currentHumidity = readHumidity();
}

void setupWaterLevelSensor() {
    pinMode(sensorsPins.waterLevel, INPUT_PULLUP);
}

float readTemperature() {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    return event.temperature;
}

float readHumidity() {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    return event.relative_humidity;
}

void updateDhtReadings() {
    currentTemp = readTemperature();
    currentHumidity = readHumidity();
}

void updateTankLevel() {
    int distanceCM = ultrasonic.read();
    
    tankLevel = 0;
    if (distanceCM <= minWaterDistance) {
        tankLevel = 100;
    }
    else if (distanceCM <= maxWaterDistance) {
        tankLevel = ((maxWaterDistance - distanceCM) / (float)(maxWaterDistance - minWaterDistance)) * 100;
    }   
    
}

bool isSensorReached() {    
    return digitalRead(sensorsPins.waterLevel) == HIGH;
}