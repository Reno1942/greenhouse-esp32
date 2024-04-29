#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Ultrasonic.h>

#define DHT_PIN 9
#define DHT_TYPE 11

DHT_Unified dht(DHT_PIN, DHT_TYPE);
uint32_t dhtDelayMS;

hd44780_I2Cexp lcd(0x27);
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

Ultrasonic hcsr04(19, 18);
int distance;

const byte fanRelay = 2;
const byte topLightRelay = 3;
const byte bottomLightRelay = 10;
const byte pumpRelay = 11;

const byte wl = 20;

// FUNCTION DECLARATIONS


void setup() {
  Serial.begin(115200);

  //setup dht
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dhtDelayMS = sensor.min_delay / 1000;

  //setup lcd
  Wire.begin(6, 7);
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
	lcd.print("Hello, World!");

  //setup relays
  pinMode(fanRelay, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(topLightRelay, OUTPUT);
  pinMode(bottomLightRelay, OUTPUT);

  digitalWrite(fanRelay, LOW);
  digitalWrite(pumpRelay, LOW);
  digitalWrite(topLightRelay, LOW);
  digitalWrite(bottomLightRelay, LOW);

  //setup wl
  pinMode(wl, INPUT);
}

void loop() {
  //ultrasonic test
  distance = hcsr04.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  //dht test
  delay(dhtDelayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  //wl test
  Serial.println(digitalRead(wl));
}

// FUNCTION DEFINITIONS