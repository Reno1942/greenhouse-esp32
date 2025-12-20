#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Serial initialized");
}

void loop() {
    Serial.println("Hello World!");
    delay(1000);
}