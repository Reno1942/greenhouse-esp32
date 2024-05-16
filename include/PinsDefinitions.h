/**
 * @file PinsDefinitions.h
*/

#ifndef PINS_DEFINITIONS_H
#define PINS_DEFINITIONS_H

#include <Arduino.h>

/**
 * @brief Defines the pin numbers for the relays.
 */
struct RelaysPins
{
    const byte topLight = 10;    /**< Pin number for the top light relay. */
    const byte bottomLight = 11; /**< Pin number for the bottom light relay. */
    const byte fan = 2;          /**< Pin number for the fan relay. */
    const byte pump = 3;         /**< Pin number for the pump relay. */
};

/**
 * @brief Defines the pin numbers for the joystick.
 */
struct JoystickPins
{
    const byte VRx = 4; /**< Pin number for the VRx joystick axis. */
    const byte VRy = 5; /**< Pin number for the VRy joystick axis. */
    const byte SW = 23; /**< Pin number for the joystick switch. */
};

/**
 * @brief Defines the pin numbers for the sensors.
 */
struct SensorsPins
{
    const byte waterLevel = 20;        /**< Pin number for the water level sensor. */
    const byte ultrasonicTrig = 19;    /**< Pin number for the ultrasonic sensor trigger. */
    const byte ultrasonicEcho = 18;    /**< Pin number for the ultrasonic sensor echo. */
    const byte dht = 9;                /**< Pin number for the DHT sensor. */
};

/**
 * @brief Defines the pin numbers for the LCD display.
 */
struct LCDPins
{
    const int sda = 6; /**< Pin number for the SDA. */
    const int scl = 7; /**< Pin number for the SCL. */
};

#endif