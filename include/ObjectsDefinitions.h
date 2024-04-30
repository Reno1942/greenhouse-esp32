#ifndef OBJECTS_DEFINITIONS_H
#define OBJECTS_DEFINITIONS_H

#include <Arduino.h>

struct LCDValues
{
    const int address = 0x27;
    const byte cols = 20;
    const byte rows = 4;    
};

struct DHTValues
{
    const byte dhtType = 11;
};

#endif