#include "Display.h"
#include "WiFiConfig.h"
#include "TimeConfig.h"

LCDValues lcdValues;
LCDPins lcdPins;

hd44780_I2Cexp lcd(lcdValues.address);

bool previousTankNeedsRefill;
bool previousAutoMode; 
bool firstAutoDisplay = true;
bool firstRefillDisplay = true;
RelayState previousRelayState[4] = {RELAY_INIT, RELAY_INIT, RELAY_INIT, RELAY_INIT};
bool previousLightOnTime = -1;
bool previousLightOffTime = -1;

void setupLCD() {
    Wire.begin(lcdPins.sda, lcdPins.scl);
    lcd.begin(lcdValues.cols, lcdValues.rows);
    lcd.backlight();        
}

void displayHomePage() {
    // row 0 title
    lcd.setCursor(1, 0);
    lcd.print("ESP32 - Greenhouse");

    // row 1 timestamp    
    char timeBuffer[17];
    if (timeinfo.tm_year > (1970 - 1900)) {
        strftime(timeBuffer, sizeof(timeBuffer), "%Y/%m/%d %H:%M", &timeinfo);
    } else {
        strncpy(timeBuffer, "Syncing time...", sizeof(timeBuffer));
    }
    lcd.setCursor(2, 1);
    lcd.print(timeBuffer);

    // row 2 tank level   
    if (previousTankNeedsRefill != tankNeedsRefill || firstRefillDisplay) {
        clearRow(2);
        lcd.setCursor(0, 2);
        lcd.print(tankNeedsRefill ? "X   Tank : Refill" : "X   Tank : Ok");       
        previousTankNeedsRefill = tankNeedsRefill;
        firstRefillDisplay = false;
    } else {
        lcd.setCursor(0, 2);
        lcd.print(previousTankNeedsRefill ? "X   Tank : Refill" : "X   Tank : Ok");
    }

    // row 3 mode
    if (previousAutoMode != autoMode || firstAutoDisplay) {
        clearRow(3);
        lcd.setCursor(0, 3);
        lcd.print(autoMode ? "X   Mode : Auto" : "X   Mode : Manual");
        previousAutoMode = autoMode;
        firstAutoDisplay = false;
    } else {
        lcd.setCursor(0, 3);
        lcd.print(previousAutoMode ? "X   Mode : Auto" : "X   Mode : Manual");
    }    
}

void displayRelaysPage() {
    String relayNames[4] = { "X   TopL", "X   BtmL", "X   Fan", "X   Pump" };
    size_t relayCount = sizeof(relayNames) / sizeof(relayNames[0]);

    for (size_t i = 0; i < relayCount; i++)
    {
        if (previousRelayState[i] != relayState[i]) {
            clearRow(i);
            lcd.setCursor(0, i);
            lcd.print(relayNames[i]);
            lcd.setCursor(9, i);
            lcd.print(": ");
            lcd.print(relayState[i] == RELAY_ON ? "On" : "Off");
            previousRelayState[i] = relayState[i]; 
        } else {
            lcd.setCursor(0, i);
            lcd.print(relayNames[i]);
            lcd.setCursor(9, i);
            lcd.print(": ");
            lcd.print(previousRelayState[i] == RELAY_ON ? "On" : "Off");
        }
    }           
}

void displaySettingsPage() {
    // row 0 light on
    if (previousLightOnTime != lightOnTime) {
        clearRow(0);
        lcd.setCursor(0, 0);
        lcd.print("X LightOn : ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOnTime);
        lcd.print(timeBuffer);
        lcd.print("H");
    }

    // row 1 light off
    if (previousLightOffTime != lightOffTime) {
        clearRow(1);
        lcd.setCursor(0, 1);
        lcd.print("X LightOff: ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOffTime);
        lcd.print(timeBuffer);
        lcd.print("H");
    }

    // row 2 day & night
    if (previousLightOnTime != lightOnTime && previousLightOffTime != lightOffTime) {
        int dayDuration = lightOffTime - lightOnTime;
        if (dayDuration < 0) dayDuration += 24;
        int nightDuration = 24 - dayDuration;
        char timeBuffer[3];

        clearRow(2);
        
        lcd.setCursor(2, 2);
        lcd.print("Day-");        
        sprintf(timeBuffer, "%02d", dayDuration);
        lcd.print(timeBuffer);
        lcd.print("H");

        
        lcd.setCursor(11, 2);
        lcd.print("Night-");        
        sprintf(timeBuffer, "%02d", nightDuration);
        lcd.print(timeBuffer);
        lcd.print("H");
    }

    // row 3 water dist        
    lcd.setCursor(2, 4);
    lcd.print("WaterDist: ");
    int waterDistanceInt = static_cast<int>(minimumWaterDistance);
    lcd.print(waterDistanceInt);
    lcd.print("cm");      
}

void clearRow(int row) {
    lcd.setCursor(0, row);
    lcd.print("                    ");
}

void clearScreen() {
    for (size_t i = 0; i < 4; i++)
    {
        clearRow(i);
    }
    
}