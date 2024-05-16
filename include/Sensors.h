/**
 * @file Sensors.h
*/

#ifndef SENSORS_H
#define SENSORS_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Ultrasonic.h>
#include "PinsDefinitions.h"

extern SensorsPins sensorsPins; /**< External declaration of SensorsPins object. */

extern float currentTemp; /**< External declaration of current temperature. */
extern float currentHumidity; /**< External declaration of current humidity. */
extern int tankLevelPercentage; /**< External declaration of tank level in percentage. */

/**
 * @brief Initializes the DHT sensor.
 */
void setupDHT();

/**
 * @brief Initializes the water level sensor.
 */
void setupWaterLevelSensor();

/**
 * @brief Reads the temperature from the DHT sensor.
 * @return The temperature value in Celsius.
 */
float readTemperature();

/**
 * @brief Reads the humidity from the DHT sensor.
 * @return The humidity value in percentage.
 */
float readHumidity();

/**
 * @brief Updates the DHT sensor readings.
 */
void updateDhtReadings();

/**
 * @brief Updates the tank level sensor reading.
 */
void updateTankLevelPercentage();

/**
 * @brief Checks if the sensor has reached the desired value.
 * @return True if the sensor has reached the desired value, false otherwise.
 */
bool isSensorReached();

#endif