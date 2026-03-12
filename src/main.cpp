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
Display display = Display(relayController, modeController, sensorController, rtc);
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
    joystick.setup();
    sensorController.setupWaterLevel();

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        modeController.setTimeTrackingMode(false);
    }

    //Heure manuelle
    //rtc.adjust(DateTime(2026, 3, 11, 20, 48, 0));

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
    display.displayDateTime();
    display.watchSleepMode();

    modeController.runOverflowProtection(currentTime);

    if (modeController.getAutoModeState() == ON) {
        modeController.runAutoMode();
    }
}