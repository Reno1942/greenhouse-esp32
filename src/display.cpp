#include <Display.h>

Display::Display(RelayController& _relayController, ModeController& _modeController, SensorController& _sensorController) :
    displayData{},
    lcdValues{.address = 0x27, .cols = 20, .rows = 4},
    lcdPins{.sda = 10, .scl = 11},
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
        lcd.print("Temp:");
        lcd.print(sensorController.readTemperature(), 0); // formatter pour 2 chiffres
        lcd.print(" C");
        resetCursor();
    }

    float currentHumidity = sensorController.readHumidity();
    if (currentHumidity != displayData.displayedHumidity) {
        displayData.displayedHumidity = currentHumidity;
        lcd.setCursor(0, 2);
        lcd.print("Hum :");
        lcd.print(sensorController.readHumidity(), 0); // formatter pour 2 chiffres
        lcd.print(" %");
        resetCursor();
    }

    int currentTankPercentage = sensorController.readTankPercentage();
    if (currentTankPercentage != displayData.displayedTankPercentage) {
        displayData.displayedTankPercentage = currentTankPercentage;
        lcd.setCursor(0, 3);
        lcd.print("Tank:");
        lcd.print(sensorController.readTankPercentage());
        lcd.print("%");
        resetCursor();
    }
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

int Display::getCurrentCursorY() {
    return currentCursorY;
}

void Display::moveCursor(CursorMoveDirection direction) {
    // TODO fix this pour avoir les relais placés de l'autre côté
    if (direction == DOWN && currentCursorY < 4) {
        currentCursorY++;
    } else if (direction == UP && currentCursorY > 0) {
        currentCursorY--;
    } else {
        return;
    }

    resetCursor();
}

void Display::resetCursor() {
    if (currentCursorY == 0) {
        lcd.setCursor(0, currentCursorY);
    } else {
        lcd.setCursor(11, currentCursorY);
    }
}
