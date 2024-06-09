#include "MQTTConfig.h"
#include "Relay.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// relay topics
const char* topLightStateTopic = "greenhouse/relays/light/top/state";
const char* topLightCommandTopic = "greenhouse/relays/light/top/command";
const char* bottomLightStateTopic = "greenhouse/relays/light/bottom/state";
const char* bottomLightCommandTopic = "greenhouse/relays/light/bottom/command";
const char* fanStateTopic = "greenhouse/relays/fan/state";
const char* fanCommandTopic = "greenhouse/relays/fan/command";
const char* pumpStateTopic = "greenhouse/relays/pump/state";
const char* pumpCommandTopic = "greenhouse/relays/pump/command";

// settings topics
const char* lightOnTimeStateTopic = "greenhouse/settings/on_time/state";
const char* lightOnTimeCommandTopic = "greenhouse/settings/on_time/command";
const char* lightOffTimeStateTopic = "greenhouse/settings/off_time/state";
const char* lightOffTimeCommandTopic = "greenhouse/settings/off_time/command";
const char* autoStateTopic = "greenhouse/settings/auto/state";
const char* autoCommandTopic = "greenhouse/settings/auto/command";

// readings topics
const char* temperatureTopic = "greenhouse/readings/temperature";
const char* humidityTopic = "greenhouse/readings/humidity";
const char* tankLevelTopic = "greennhouse/readings/tank_level";

TopicHandler topicHandlers[] = {
    {topLightCommandTopic, handleTopLightCommand},
    {bottomLightCommandTopic, handleBottomLightCommand},
    {fanCommandTopic, handleFanCommand},
    {pumpCommandTopic, handlePumpCommand},
    {lightOnTimeCommandTopic, handleLightOnTimeCommand},
    {lightOffTimeCommandTopic, handleLightOffTimeCommand},
    {autoCommandTopic, handleAutoCommand}
};

void mqttCallback(char* topic, byte* payload, unsigned int length) { 
    Serial.println("mqttCallback called");

    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';

    Serial.print("Received topic: ");
    Serial.println(topic);
    Serial.print("Received message: ");
    Serial.println(message);

    for (TopicHandler& th : topicHandlers)
    {
        Serial.print("Checking topic: ");
        Serial.println(th.topic);

        if (strcmp(topic, th.topic) == 0) {
            Serial.println("Topic match found, calling handler");
            th.handler(message);
            break;
        }
    }    
}

void setupMQTT() {
    const unsigned long mqttTimeout = 10000;
    unsigned long startTime = millis();

    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    Serial.print("Connecting to MQTT broker ");

    while (!mqttClient.connected()) {
        if (mqttClient.connect("ESP32Client")) {
            Serial.println("Connected to MQTT broker"); 
            mqttClient.setCallback(mqttCallback);    
            mqttClient.subscribe(topLightCommandTopic);
            mqttClient.subscribe(bottomLightCommandTopic);
            mqttClient.subscribe(fanCommandTopic);
            mqttClient.subscribe(pumpCommandTopic);
            mqttClient.subscribe(lightOnTimeCommandTopic);
            mqttClient.subscribe(lightOffTimeCommandTopic);
            mqttClient.subscribe(autoCommandTopic);
        }
        else if (millis() - startTime >= mqttTimeout) {
            Serial.println("MQTT connection failed");  
            return;          
        }

        delay(500);        
    }
}

bool publishMessage(const char* topic, const char* message, const char* logMessage) {
    if (mqttClient.connected()) {
        bool published = mqttClient.publish(topic, message);
        //Serial.println(published ? String(logMessage) + " published" : String(logMessage) + " publish failed"); 
        return published;       
    } else {
        Serial.println("MQTT client is not connected");
        return false;
    }
}

void publishLightTime(const char* topic, int time) {
    char message[3];
    sprintf(message, "%02d", time);

    publishMessage(topic, message, "LightTime");
}

void publishRelayState(const char* topic, const char* state) {
    publishMessage(topic, state, "RelayState");
}

void publishHumidity(float humidity) {
    char message[5];
    sprintf(message, "%.1f", humidity);

    publishMessage(humidityTopic, message, "Humidity");
}

void publishTemperature(float temperature) {
    char message[5];
    sprintf(message, "%.1f", temperature);

    publishMessage(temperatureTopic, message, "Temperature");
}

void publishTankLevel(int level) {
    char message[4];
    sprintf(message, "%d", level);

    publishMessage(tankLevelTopic, message, "Tank Level");
}

void publishAutoMode(bool state) {
    const char* message = (state ? "ON" : "OFF");
    publishMessage(autoStateTopic, message, "AutoMode");
}

void handleTopLightCommand(const char* message) {
    if (!autoMode) {
        toggleRelay(relaysPins.topLight, TopL);
    }        
}

void handleBottomLightCommand(const char* message) {
    if (!autoMode) {
        toggleRelay(relaysPins.bottomLight, BtmL);
    }    
}

void handleFanCommand(const char* message) {
    if (!autoMode) {
        toggleRelay(relaysPins.fan, Fan);
    }    
}

void handlePumpCommand(const char* message) {
    if (!autoMode) {
        toggleRelay(relaysPins.pump, Pump);
    }    
}

void handleLightOnTimeCommand(const char* message) {
    int newLightOnTime = atoi(message);
    if (newLightOnTime >= 0 && newLightOnTime < 24 && newLightOnTime != lightOffTime) {
        lightOnTime = newLightOnTime;
        publishLightTime(lightOnTimeStateTopic, lightOnTime);
    } else {
        Serial.println("Request denied : Time invalid");
    }
}

void handleLightOffTimeCommand(const char* message) {
    int newLightOffTime = atoi(message);
    if (newLightOffTime >= 0 && newLightOffTime < 24 && newLightOffTime != lightOnTime) {
        lightOffTime = atoi(message);
        publishLightTime(lightOffTimeStateTopic, lightOffTime);
    } else {
        Serial.println("Request denied : Time invalid");
    }
}

void handleAutoCommand(const char* message) {
    if (strcmp(message, "ON") == 0) {
        autoMode = true;        
    } else if (strcmp(message, "OFF") == 0) {
        autoMode = false;
    }

    publishAutoMode(autoMode);
}