#include "Display.h"
#include "WiFiConfig.h"
#include "TimeConfig.h"

LCDValues lcdValues;
LCDPins lcdPins;

hd44780_I2Cexp lcd(lcdValues.address);

bool firstTankDisplay = true;
bool firstAutoDisplay = true;
bool firstRelayDisplay = true;

bool previousTankNeedsRefill = false;
bool previousAutoMode = false; 
bool previousRelayState[4] = { false, false, false, false };

void setupLCD() {
    Wire.begin(lcdPins.sda, lcdPins.scl);
    lcd.begin(lcdValues.cols, lcdValues.rows);
    lcd.backlight();      
}

void displayHomePage() {
    // row 0
    lcd.setCursor(1, 0);
    lcd.print("ESP32 - Greenhouse");

    // row 1 timestamp    
    char timeBuffer[17]; // "YYYY/MM/dd HH:mm\0"
    if (timeinfo.tm_year > (1970 - 1900)) {
    strftime(timeBuffer, sizeof(timeBuffer), "%Y/%m/%d %H:%M", &timeinfo);
    } else {
        strncpy(timeBuffer, "Syncing time...", sizeof(timeBuffer));
    }
    lcd.setCursor(2, 1);
    lcd.print(timeBuffer);

    // row 2 tank level   
    if (firstTankDisplay || previousTankNeedsRefill != tankNeedsRefill) {
        clearRow(2);
        lcd.setCursor(4, 2);
        if (tankNeedsRefill) {
            lcd.print("Tank : Refill");
        } else {
            lcd.print("Tank : Ok");
        }
        firstTankDisplay = false;
        previousTankNeedsRefill = tankNeedsRefill;
    }

    // row 3 mode
    if (firstAutoDisplay || previousAutoMode != autoMode) {
        clearRow(3);
        lcd.setCursor(4, 3);
        if (autoMode) {
            lcd.print("Mode : Auto");
        } else {
            lcd.print("Mode : Manual");
        }
        firstAutoDisplay = false;
        previousAutoMode = autoMode;
    }
}

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

void clearRow(int row) {
    lcd.setCursor(0, row);
    lcd.print("                    ");
}