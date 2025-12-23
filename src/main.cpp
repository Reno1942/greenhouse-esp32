#include <Arduino.h>
#include "WiFiController.h"
#include "Display.h"
#include "Joystick.h"
#include "RelayController.h"

WiFiController wifiController = WiFiController();
RelayController relayController = RelayController();
SensorController sensorController = SensorController();
ModeController modeController = ModeController(relayController);
Display display = Display(relayController, modeController, sensorController);
Joystick joystick = Joystick(display, relayController, modeController);

unsigned long currentTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Serial initialized");

    wifiController.setup();

    display.setup();
    relayController.setupRelays();
    sensorController.setupDHT();
    sensorController.setupWaterLevel();
}

void loop() {
    currentTime = millis();

    joystick.handleJoystickMovement(currentTime);
    joystick.handleJoystickClick(currentTime);

    display.displayRelays();
    display.displaySensors();
    display.displayAutoMode();

    modeController.runAutoMode();
}