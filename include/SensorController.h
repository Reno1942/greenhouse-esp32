#ifndef GREENHOUSE_ESP32_SENSORHANDLER_H
#define GREENHOUSE_ESP32_SENSORHANDLER_H

#include <DHT.h>
#include <DHT_U.h>
#include <Ultrasonic.h>

struct SensorsPins {
    uint8_t waterLevel;
    uint8_t ultrasonicTrig;
    uint8_t ultrasonicEcho;
    uint8_t dht;
};

class SensorController {
public:
    SensorController();
    void setupWaterLevel();
    void setupDHT();
    float readTemperature();
    float readHumidity();
    int readTankPercentage();
    bool wlSensorReached();

private:
    SensorsPins sensorsPins;
    DHT_Unified dht;
    Ultrasonic ultrasonic;

    const int minWaterDistance = 5;
    const int maxWaterDistance = 30;

    sensors_event_t temperatureEvent;
    sensors_event_t humidityEvent;
    int tankLevelPercentage = 0;
};

#endif //GREENHOUSE_ESP32_SENSORHANDLER_H