#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#include "RelayHandler.h"

struct DisplayData {
    float temperature;
    float humidity;
    int tankLevelPercentage;
    bool isAutoModeOn;
    Relay relays[4];    
};

#endif