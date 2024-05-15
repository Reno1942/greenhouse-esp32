#include "Sensors.h"

DHT_Unified dht(sensorsPins.dht, 11);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);


void setupDHT() {
    dht.begin();
    currentTemp = readTemperature();
    currentHumidity = readHumidity();
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