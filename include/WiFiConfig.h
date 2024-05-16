/**
 * WiFiConfig.h
*/

#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include "Credentials.h"

/**
 * @brief Extern declaration of WiFiClass, gives access to WiFi functionnalities on the ESP32.
 */
extern WiFiClass WiFi;

/**
 * @brief Sets up the WiFi.
*/
void setupWifi();

#endif