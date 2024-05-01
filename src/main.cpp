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

// other variables
int currentCursorY = 0;
bool joystickMoved = false;

// function declarations
void setupLCD();
void setupJoystick();
void handleJoystickControl();

void setup() {
    Serial.begin(115200);  

    setupLCD();
    setupJoystick();
}

void loop() {    
    handleJoystickControl();    
}

// function definitions
void setupLCD() {
    Wire.begin(lcdPins.sda, lcdPins.scl);
    lcd.begin(lcdValues.cols, lcdValues.rows);
    lcd.backlight();
    lcd.blink();    
}

void setupJoystick() {
    pinMode(joystickPins.SW, INPUT_PULLUP);
    pinMode(joystickPins.VRx, INPUT);
    pinMode(joystickPins.VRy, INPUT);
}

void handleJoystickControl() {
    // margin for center return and center
    int joystickCenter = 2449;
    int joystickCenterMargin = 1000;    

    // read the current joystick position, baseline is approx. 2449
    int joystickY = analogRead(joystickPins.VRy);
    
    // reset joystick moving if is near the center
    if (abs(joystickY - joystickCenter) <= joystickCenterMargin) {
        joystickMoved = false;
    }

    // move cursor up if joystick moved up
    if (joystickY < joystickCenter - joystickCenterMargin && currentCursorY > 0 && !joystickMoved) {
        currentCursorY--;
        joystickMoved = true;
    }

    // move cursor down if joystick moved down
    if (joystickY > joystickCenter + joystickCenterMargin && currentCursorY < 3 && !joystickMoved) {
        currentCursorY++;
        joystickMoved = true;
    }

    // move lcd cursor
    lcd.setCursor(0, currentCursorY);
}