#include "Display.h"
#include "WiFiConfig.h"
#include "TimeConfig.h"

LCDValues lcdValues;
LCDPins lcdPins;

hd44780_I2Cexp lcd(lcdValues.address);

bool refreshHomePage = true;
bool refreshRelaysPage = true;
bool refreshSettingsPage = true;

bool previousTankNeedsRefill;
bool previousAutoMode; 
String previousTimeBuffer = "";
RelayState previousRelayState[4] = {RELAY_INIT, RELAY_INIT, RELAY_INIT, RELAY_INIT};
int previousLightOnTime = -1;
int previousLightOffTime = -1;
float previousTemp = -1;
float previousHumidity = -1;

void setupLCD() {
    Wire.begin(lcdPins.sda, lcdPins.scl);
    lcd.begin(lcdValues.cols, lcdValues.rows);
    lcd.backlight();   
    lcd.blink();         
}

void displayHomePage() {
    // row 0 title    
    if (refreshHomePage || previousTemp != currentTemp || previousHumidity != currentHumidity) {
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(currentTemp, 1);
        lcd.print("C Hum:");
        lcd.print(currentHumidity, 1);
        lcd.print("%");
        previousTemp = currentTemp;
        previousHumidity = currentHumidity;
    }    

    // row 1 timestamp    
    char timeBuffer[17];
    if (timeinfo.tm_year > (1970 - 1900)) {
        strftime(timeBuffer, sizeof(timeBuffer), "%Y/%m/%d %H:%M", &timeinfo);
    } else {
        strncpy(timeBuffer, "Syncing time...", sizeof(timeBuffer));
    }
    if (refreshHomePage || previousTimeBuffer != timeBuffer) {
        lcd.setCursor(2, 1);
        lcd.print(timeBuffer);  
        previousTimeBuffer = timeBuffer;
    }
      

    // row 2 tank level   
    if (refreshHomePage || previousTankNeedsRefill != tankNeedsRefill) {
        clearRow(2);
        lcd.setCursor(4, 2);
        lcd.print(tankNeedsRefill ? "Tank : Refill" : "Tank : Ok");       
        previousTankNeedsRefill = tankNeedsRefill;        
    }

    // row 3 mode
    if (refreshHomePage || previousAutoMode != autoMode) {
        clearRow(3);
        lcd.setCursor(0, 3);
        lcd.print(autoMode ? "X   Mode : Auto" : "X   Mode : Manual");
        previousAutoMode = autoMode;        
    }     
    updateCursor();
    refreshHomePage = false; 
}

void displayRelaysPage() {
    String relayNames[4] = { "X   TopL", "X   BtmL", "X   Fan", "X   Pump" };
    size_t relayCount = sizeof(relayNames) / sizeof(relayNames[0]);

    for (size_t i = 0; i < relayCount; i++)
    {
        if (refreshRelaysPage || previousRelayState[i] != relayState[i]) {
            clearRow(i);
            lcd.setCursor(0, i);
            lcd.print(relayNames[i]);
            lcd.setCursor(9, i);
            lcd.print(": ");
            lcd.print(relayState[i] == RELAY_ON ? "On" : "Off");
            previousRelayState[i] = relayState[i]; 
        }
    }  
    refreshRelaysPage = false;    
    updateCursor();     
}

void displaySettingsPage() {
    // row 0 light on
    if (refreshSettingsPage || previousLightOnTime != lightOnTime) {
        clearRow(0);
        lcd.setCursor(0, 0);
        lcd.print("X LightOn : ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOnTime);
        lcd.print(timeBuffer);
        lcd.print("H");

        previousLightOnTime = lightOnTime;
    }

    // row 1 light off
    if (refreshSettingsPage || previousLightOffTime != lightOffTime) {
        clearRow(1);
        lcd.setCursor(0, 1);
        lcd.print("X LightOff: ");

        char timeBuffer[3];
        sprintf(timeBuffer, "%02d", lightOffTime);
        lcd.print(timeBuffer);
        lcd.print("H");

        previousLightOffTime = lightOffTime;
    }

    // row 2 day & night
    if (refreshSettingsPage || previousLightOnTime != lightOnTime || previousLightOffTime != lightOffTime) {
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
    
    refreshSettingsPage = false;
    updateCursor();
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

void updateCursor() {    
    lcd.setCursor(0, currentCursorY);    
}