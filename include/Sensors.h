#ifndef SENSORS_H
#define SENSORS_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Ultrasonic.h>
#include "PinsDefinitions.h"

extern SensorsPins sensorsPins;

extern float currentTemp;
extern float currentHumidity;
extern int tankLevel;

void setupDHT();
void setupWaterLevelSensor();
float readTemperature();
float readHumidity();
void updateDhtReadings();
void updateTankLevel();
bool isSensorReached();

#endif