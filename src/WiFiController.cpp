// #include <WiFiController.h>
//
// bool WiFiController::getUsingRealTime() {
//     return usingRealTime;
// }
//
// WiFiController::WiFiController() {
// }
//
// void WiFiController::setup() {
//     WiFi.mode(WIFI_MODE_STA);
//     WiFi.disconnect(true);
//     delay(100);
//
//     Serial.print("Connecting to WiFi");
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//
//     unsigned long startAttemptTime = millis();
//     const unsigned long timeout = 15000;
//
//     while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
//         delay(500);
//         Serial.print(".");
//     }
//
//     if (WiFi.status() == WL_CONNECTED) {
//         Serial.println("\nWiFi connected");
//         setupTime();
//     } else {
//         Serial.println("WiFi not connected");
//         usingRealTime = false;
//     }
// }
//
// void WiFiController::setupTime() {
//     Serial.println("Obtaining time from NTP");
//     configTime(-5 * 3600, 3600, "pool.ntp.org", "time.nist.gov");
//
//     struct tm timeinfo;
//     int retries = 0;
//     while (!getLocalTime(&timeinfo) && retries < 10) {
//         delay(500);
//         retries++;
//     }
//
//     if (getLocalTime(&timeinfo)) {
//         Serial.println("Real time obtained from NTP");
//         usingRealTime = true;
//     } else {
//         Serial.println("Time could not be obtained from NTP");
//         usingRealTime = false;
//     }
//
//     delay(500);
//     WiFi.disconnect(true);
//     delay(500);
//     WiFi.mode(WIFI_OFF);
//     delay(500);
//     Serial.println("WiFi disconnected");
// }
