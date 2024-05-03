// libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <Ultrasonic.h>

// local includes
#include "PinsDefinitions.h"
#include "Display.h"

// enums
enum RelayState : byte 
{
    RELAY_OFF = 1,
    RELAY_ON = 0
};

// pin structs
RelaysPins relaysPins;
SensorsPins sensorsPins;
JoystickPins joystickPins;

// objects creation
DHT_Unified dht(sensorsPins.dht, 11);
Ultrasonic ultrasonic(sensorsPins.ultrasonicTrig, sensorsPins.ultrasonicEcho);

// other variables
int currentCursorY = 0;
bool joystickMoved = false;
bool tankNeedsRefill = false;
bool autoMode = false;
bool relayState[4] = { false, false, false, false };

// function declarations
void setupJoystick();
void setupRelays();

void handleJoystickControl();
void toggleRelay(byte relayPin);

void setup() {
    Serial.begin(115200);  

    setupRelays();
    setupLCD();
    setupJoystick();
}

void loop() {    
    handleJoystickControl();   
    // displayHomePage();
    displayRelaysPage();       
}

// function definitions
void setupJoystick() {
    pinMode(joystickPins.SW, INPUT_PULLUP);
    pinMode(joystickPins.VRx, INPUT);
    pinMode(joystickPins.VRy, INPUT);
}

void setupRelays() {
    pinMode(relaysPins.topLight, OUTPUT);
    pinMode(relaysPins.bottomLight, OUTPUT);
    pinMode(relaysPins.pump, OUTPUT);
    pinMode(relaysPins.fan, OUTPUT);

    digitalWrite(relaysPins.topLight, RELAY_OFF);
    digitalWrite(relaysPins.bottomLight, RELAY_OFF);
    digitalWrite(relaysPins.pump, RELAY_OFF);
    digitalWrite(relaysPins.fan, RELAY_OFF);
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
    //lcd.setCursor(0, currentCursorY);
}

void toggleRelay(byte relayPin) {
    int state = digitalRead(relayPin);
    digitalWrite(relayPin, !state);
}