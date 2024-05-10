#include "Display.h"
#include "WiFiConfig.h"
#include "TimeConfig.h"

LCDValues lcdValues;
LCDPins lcdPins;

hd44780_I2Cexp lcd(lcdValues.address);

bool previousTankNeedsRefill;
bool previousAutoMode; 
bool previousRelayState[4];
bool previousLightOnTime;
bool previousLightOffTime;

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
    if (previousTankNeedsRefill != tankNeedsRefill) {
        clearRow(2);
        lcd.setCursor(4, 2);
        if (tankNeedsRefill) {
            lcd.print("Tank : Refill");
        } else {
            lcd.print("Tank : Ok");
        }        
        previousTankNeedsRefill = tankNeedsRefill;
    }

    // row 3 mode
    if (previousAutoMode != autoMode) {
        clearRow(3);
        lcd.setCursor(4, 3);
        if (autoMode) {
            lcd.print("Mode : Auto");
        } else {
            lcd.print("Mode : Manual");
        }
        previousAutoMode = autoMode;
    }
}

// TODO : check logic of this seems uselessly complicated, how to tell which relay is in previousRelaysState etc
void displayRelaysPage() {
    String relayNames[4] = { "TopL", "BtmL", "Fan", "Pump" };
    size_t relayCount = sizeof(relayNames) / sizeof(relayNames[0]);

    for (size_t i = 0; i < relayCount; i++)
    {
        if (firstRelayDisplay || previousRelayState[i] != relayState[i]) {
            clearRow(i);
            lcd.setCursor(4, i);
            lcd.print(relayNames[i]);
            lcd.setCursor(9, i);
            lcd.print(": ");
            lcd.print(relayState[i] ? "On" : "Off");
            previousRelayState[i] = relayState[i]; 
        }
    }
    
    if (firstRelayDisplay) {
        firstRelayDisplay = false;
    }
}

void displaySettingsPage() {
    // row 0 light on
    if (previousLightOnTime != lightOnTime) {
        clearRow(0);
        lcd.setCursor(1, 0);
        lcd.print("LightOn : ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOnTime);
        lcd.print(timeBuffer);
    }

    // row 1 light off
    if (previousLightOffTime != lightOffTime) {
        clearRow(1);
        lcd.setCursor(1, 1);
        lcd.print("LightOff : ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOffTime);
        lcd.print(timeBuffer);
    }

    // row 2 day & night
    if (previousLightOnTime != lightOnTime && previousLightOffTime != lightOffTime) {
        int dayDuration = lightOffTime - lightOnTime;
        if (dayDuration < 0) dayDuration += 24;
        int nightDuration = 24 - dayDuration;
        char timeBuffer[3];

        clearRow(2);
        
        lcd.setCursor(1, 2);
        lcd.print("Day-");        
        sprintf(timeBuffer, "%02d", dayDuration);
        lcd.print(timeBuffer);
        lcd.print("H");

        
        lcd.setCursor(10, 2);
        lcd.print("Night-");        
        sprintf(timeBuffer, "%02d", nightDuration);
        lcd.print("H");
    }

    // row 3 water dist        
    lcd.setCursor(1, 4);
    lcd.print("WaterDist: ");
    int waterDistanceInt = static_cast<int>(minimumWaterDistance);
    lcd.print(waterDistanceInt);
}

void clearRow(int row) {
    lcd.setCursor(0, row);
    lcd.print("                    ");
}