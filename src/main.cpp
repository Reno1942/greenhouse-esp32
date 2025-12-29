#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>
#include "Display.h"
#include "Joystick.h"
#include "RelayController.h"

RTC_DS1307 rtc;
RelayController relayController = RelayController();
SensorController sensorController = SensorController();
ModeController modeController = ModeController(relayController, sensorController, rtc);
Display display = Display(relayController, modeController, sensorController);
Joystick joystick = Joystick(display, relayController, modeController);

unsigned long currentTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("BOOT START");
    Serial.print("Reset reason: ");
    Serial.println(esp_reset_reason());

    display.setup();
    relayController.setupRelays();
    sensorController.setupDHT();
    sensorController.setupWaterLevel();

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        modeController.setTimeTrackingMode(false);
    }

    if (!rtc.isrunning()) {
        Serial.println("RTC is not running, setting time");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    } else {
        Serial.print("RTC is running : ");
        Serial.println(rtc.now().timestamp());
    }

    Serial.println("Setup finished");
}

void loop() {
    currentTime = millis();

    joystick.handleJoystickMovement(currentTime);
    joystick.handleJoystickClick(currentTime);

    display.displayRelays();
    display.displaySensors();
    display.displayAutoMode();

    //modeController.runOverflowProtection(currentTime);

    if (modeController.getAutoModeState() == ON) {
        modeController.runAutoMode();
    }
}