// libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Ultrasonic.h>

// local includes
#include "PinsDefinitions.h"
#include "ObjectsDefinitions.h"

// enums
enum RelayState : byte 
{
    RELAY_OFF = 1,
    RELAY_ON = 0
};

// pin structs
RelaysPins relaysPins;
SensorsPins sensorsPins;
LCDPins lcdPins;
JoystickPins joystickPins;

// objects structs
LCDValues lcdValues;
DHTValues dhtValues;

// objects creation
DHT_Unified dht(sensorsPins.dht, dhtValues.dhtType);
hd44780_I2Cexp lcd(lcdValues.address);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);

// function declarations
void setupLCD();
void setupJoystick();

void setup() {
    Serial.begin(115200);  

    setupLCD();
    setupJoystick();
}

void loop() {    
}

// function definitions
void setupLCD()
{
    Wire.begin(lcdPins.sda, lcdPins.scl);
    lcd.begin(lcdValues.cols, lcdValues.rows);
    lcd.backlight();
    lcd.blink();    
}

void setupJoystick()
{
    pinMode(joystickPins.SW, INPUT);
    pinMode(joystickPins.VRx, INPUT);
    pinMode(joystickPins.VRy, INPUT);
}