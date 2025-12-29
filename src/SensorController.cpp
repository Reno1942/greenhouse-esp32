#include "SensorController.h"

SensorController::SensorController() :
    sensorsPins{
        .waterLevelGutter = 0,
        .waterLevelTank = 1,
        .ultrasonicTrig = 12,
        .ultrasonicEcho = 13,
        .dht = 7
    },
    dht(sensorsPins.dht, 11)
    //ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho)
{}

void SensorController::setupDHT() {
    dht.begin();
}

void SensorController::setupWaterLevel() {
    pinMode(sensorsPins.waterLevelGutter, INPUT_PULLUP);
    pinMode(sensorsPins.waterLevelTank, INPUT_PULLUP);
}

float SensorController::readTemperature() {
    dht.temperature().getEvent(&temperatureEvent);
    return temperatureEvent.temperature;
}

float SensorController::readHumidity() {
    dht.humidity().getEvent(&humidityEvent);
    return humidityEvent.relative_humidity;
}


// int SensorController::readTankPercentage() {
//     int distanceCM = ultrasonic.read();
//
//     if (distanceCM <= minWaterDistance) {
//         tankLevelPercentage = 100;
//     }
//     else if (distanceCM <= maxWaterDistance) {
//         tankLevelPercentage = ((maxWaterDistance - distanceCM) / static_cast<float>(maxWaterDistance - minWaterDistance)) * 100;
//     }
//
//     return tankLevelPercentage;
// }

bool SensorController::waterLevelGutterReached() {
    return digitalRead(sensorsPins.waterLevelGutter) == 1;
}

bool SensorController::waterLevelTankReached() {
    return digitalRead(sensorsPins.waterLevelTank) == 1;
}
