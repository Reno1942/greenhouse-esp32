#include <Display.h>

Display::Display(RelayController& _relayController, ModeController& _modeController, SensorController& _sensorController) :
    displayData{},
    lcdValues{.address = 0x27, .cols = 20, .rows = 4},
    lcdPins{.sda = 1, .scl = 2},
    relayController(_relayController),
    modeController(_modeController),
    sensorController(_sensorController)
{
}

bool Display::setup() {
    bool wireInitStatus = Wire.begin(lcdPins.sda, lcdPins.scl);
    if (!wireInitStatus) {
        Serial.println("LCD: Wire initialization failed");
        return false;
    }
    Serial.println("LCD: Wire initialized");

    delay(500);

    int lcdInitStatus = lcd.begin(lcdValues.cols, lcdValues.rows);
    if (lcdInitStatus == 0) {
        Serial.println("LCD: Setting up");
        lcd.clear();
        lcd.backlight();
        lcd.blink();

        Serial.println("LCD: Initialized");
        return true;
    }

    Serial.print("LCD: LCD initialization failed with status ");
    Serial.println(lcdInitStatus);
    return false;
}

void Display::displayRelays() {
    auto &relays = relayController.getRelays();
    int row = 0;

    for (auto &[name, relay]: relays) {
        if (displayData.displayedRelayStates[name] != relay.state) {
            displayData.displayedRelayStates[name] = relay.state;

            lcd.setCursor(10, row);
            lcd.print("> ");
            lcd.print(name);
            lcd.setCursor(17, row);
            if (relay.state == RELAY_ON) {
                lcd.print("On ");
            } else {
                lcd.print("Off");
            }
        }
        row++;
    }
    resetCursor();
}

void Display::displaySensors() {
    float currentTemperature = sensorController.readTemperature();
    if (currentTemperature != displayData.displayedTemperature) {
        displayData.displayedTemperature = currentTemperature;
        lcd.setCursor(0, 1);
        lcd.print("Tem:");
        lcd.print(sensorController.readTemperature());
        lcd.setCursor(8, 1);
        lcd.print("C");
        resetCursor();
    }

    float currentHumidity = sensorController.readHumidity();
    if (currentHumidity != displayData.displayedHumidity) {
        displayData.displayedHumidity = currentHumidity;
        lcd.setCursor(0, 2);
        lcd.print("Hum:");
        lcd.print(sensorController.readHumidity());
        lcd.setCursor(8, 2);
        lcd.print("%");
        resetCursor();
    }

    // int currentTankPercentage = sensorController.readTankPercentage();
    // if (currentTankPercentage != displayData.displayedTankPercentage) {
    //     displayData.displayedTankPercentage = currentTankPercentage;
    //     lcd.setCursor(0, 3);
    //     lcd.print("Tank:");
    //     lcd.print(sensorController.readTankPercentage());
    //     lcd.setCursor(8, 3);
    //     lcd.print("%");
    //     resetCursor();
    // }
}

void Display::displayAutoMode() {
    AutoModeState currentAutoModeState = modeController.getAutoModeState();
    if (currentAutoModeState != displayData.displayedAutoModeState) {
        displayData.displayedAutoModeState = currentAutoModeState;
        lcd.setCursor(0, 0);
        lcd.print("> ");

        if (currentAutoModeState == ON) {
            lcd.print("Auto  ");
        } else {
            lcd.print("Manuel");
        }
        resetCursor();
    }
}

int Display::getCursorPosition() {
    return cursorPosition;
}

void Display::moveCursor(CursorMoveDirection direction) {
    if (direction == DOWN && cursorPosition < 4) {
        cursorPosition++;
    } else if (direction == UP && cursorPosition > 0) {
        cursorPosition--;
    } else {
        return;
    }

    resetCursor();
}

void Display::resetCursor() {
    if (cursorPosition == 0) {
        lcd.setCursor(0, cursorPosition);
    } else {
        // on retire un pour placer comme il faut dans la 2eme col
        lcd.setCursor(10, cursorPosition - 1);
    }
}
