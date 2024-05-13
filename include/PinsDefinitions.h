#ifndef PINS_DEFINITIONS_H
#define PINS_DEFINITIONS_H

#include <Arduino.h>

struct RelaysPins
{
    const byte topLight = 10;
    const byte bottomLight = 11;  
    const byte fan = 2;
    const byte pump = 3;    
};

struct JoystickPins
{
    const byte VRx = 4;
    const byte VRy = 5;
    const byte SW = 23;
};

struct SensorsPins
{
    const byte waterLevel = 20;
    const byte ultrasonicTrig = 19;
    const byte ultrasonicEcho = 18;
    const byte dht = 9;    
};

struct LCDPins
{
    const int sda = 6;
    const int scl = 7;
};

#endif