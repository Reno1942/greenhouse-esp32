# Greenhouse - ESP32

**Code for a greenhouse built on a ESP32-C6-DevKitC-1.**

<hr></hr>

### DevKit Pinout

![ESP32-C6-DevKitC-1 Pinout](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/_images/esp32-c6-devkitc-1-pin-layout.png)

### Default Connections

| GPIO Pin | Connection           |
|----------|----------------------|
| 21       | Top Light Relay      |
| 20       | Bottom Light Relay   |
| 23       | Fan Relay            |
| 22       | Pump Relay           |
| 4        | VRx (Joystick)       |
| 5        | VRy (Joystick)       |
| 3        | SW (Joystick)        |
| 10       | SDA (LCD & RTC)      |
| 11       | SCL (LCD & RTC)      |
| 0        | DHT-11               |
| 1        | Water Level (Gutter) |
| 7        | Water Level (Tank)   |