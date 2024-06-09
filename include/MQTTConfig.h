/**
 * MQTTConfig.h
 */

#ifndef MQTTCONFIG_H
#define MQTTCONFIG_H

#include <PubSubClient.h>
#include <WiFiClient.h>
#include "Credentials.h"

// relay topics
extern const char* topLightStateTopic;
extern const char* topLightCommandTopic;
extern const char* bottomLightStateTopic;
extern const char* bottomLightCommandTopic;
extern const char* fanStateTopic;
extern const char* fanCommandTopic;
extern const char* pumpStateTopic;
extern const char* pumpCommandTopic;

// settings topics
extern const char* lightOnTimeStateTopic;
extern const char* lightOnTimeCommandTopic;
extern const char* lightOffTimeStateTopic;
extern const char* lightOffTimeCommandTopic;
extern const char* autoStateTopic;
extern const char* autoCommandTopic;

// readings topics
extern const char* temperatureTopic;
extern const char* humidityTopic;
extern const char* tankLevelTopic;

struct TopicHandler {
    const char* topic;
    void (*handler)(const char*);
};

extern int lightOnTime;
extern int lightOffTime;
extern bool autoMode;

/**
 * @brief Sets up the MQTT server.
 */
void setupMQTT();

bool publishMessage(const char* topic, const char* message, const char* logMessage);
void publishLightTime(const char* topic, int time);
void publishRelayState(const char* topic, const char* state);
void publishHumidity(float humidity);
void publishTemperature(float temperature);
void publishTankLevel(int level);
void publishAutoMode(bool state);

void handleTopLightCommand(const char* message);
void handleBottomLightCommand(const char* message);
void handleFanCommand(const char* message);
void handlePumpCommand(const char* message);
void handleLightOnTimeCommand(const char* message);
void handleLightOffTimeCommand(const char* message);
void handleAutoCommand(const char* message);

#endif