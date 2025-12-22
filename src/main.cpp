#include <Arduino.h>
#include "Display.h"
#include "Joystick.h"
#include "RelayController.h"

RelayController relayController = RelayController();
SensorController sensorController = SensorController();
ModeController modeController = ModeController();
Display display = Display(relayController, modeController, sensorController);
Joystick joystick = Joystick(display);

unsigned long currentTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Serial initialized");

    display.setup();
    relayController.setupRelays();
    sensorController.setupDHT();
    sensorController.setupWaterLevel();
}

void loop() {
    currentTime = millis();

    joystick.handleJoystickMovement(currentTime);

    display.displayRelays();
    display.displaySensors();
    display.displayAutoMode();
}