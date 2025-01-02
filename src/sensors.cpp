#include "Sensors.h"

DHT_Unified dht(sensorsPins.dht, 11);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);

const int minWaterDistance = 5;
const int maxWaterDistance = 37;

void setupDHT() {
    Serial.println("Setting up DHT");

    dht.begin();
    currentTemp = readTemperature();
    currentHumidity = readHumidity();
}

void setupWaterLevelSensor() {
    Serial.println("Setting up WL Sensor");
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

void updateTankLevelPercentage() {
    int distanceCM = ultrasonic.read();
    
    tankLevelPercentage = 0;
    if (distanceCM <= minWaterDistance) {
        tankLevelPercentage = 100;
    }
    else if (distanceCM <= maxWaterDistance) {
        tankLevelPercentage = ((maxWaterDistance - distanceCM) / (float)(maxWaterDistance - minWaterDistance)) * 100;
    }   
    
}

bool isSensorReached() {    
    return digitalRead(sensorsPins.waterLevel) == HIGH;
}