#include "MQTTConfig.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// relay topics
const char* topLightStateTopic = "greenhouse/33/relays/TopLight/state";
const char* topLightCommandTopic = "greenhouse/33/relays/TopLight/command";
const char* bottomLightStateTopic = "greenhouse/33/relays/BottomLight/state";
const char* bottomLightCommandTopic = "greenhouse/33/relays/BottomLight/command";
const char* fanStateTopic = "greenhouse/33/relays/Fan/state";
const char* fanCommandTopic = "greenhouse/33/relays/Fan/command";
const char* pumpStateTopic = "greenhouse/33/relays/Pump/state";
const char* pumpCommandTopic = "greenhouse/33/relays/Pump/command";

// settings topics
const char* lightOnTimeStateTopic = "greenhouse/33/settings/LightOnTime/state";
const char* lightOnTimeCommandTopic = "greenhouse/33/settings/LightOnTime/command";
const char* lightOffTimeStateTopic = "greenhouse/33/settings/LightOffTime/state";
const char* lightOffTimeCommandTopic = "greenhouse/33/settings/LightOffTime/command";
const char* autoStateTopic = "greenhouse/33/settings/AutoMode/state";
const char* autoCommandTopic = "greenhouse/33/settings/AutoMode/command";

// readings topics
const char* temperatureTopic = "greenhouse/33/readings/DHT-11/Temperature";
const char* humidityTopic = "greenhouse/33/readings/DHT-11/Humidity";
const char* tankLevelTopic = "greenhouse/33/readings/Ultrasonic/TankLevel";

TopicHandler topicHandlers[] = {
    // {topLightCommandTopic, [](const char* message) { handleRelayCommand(message, relaysPins.topLight, TopL); }},
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
        if (mqttClient.connect("33")) {
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
        //Serial.println("MQTT client is not connected");
        return false;
    }
}

void publishLightTime(const char* topic, int time) {
    char message[3];
    sprintf(message, "%d", time);
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
    const char* message = (state ? "true" : "false");
    publishMessage(autoStateTopic, message, "AutoMode");
}

void handleRelayCommand(const char* message, int relayPin, RelayIndex relayIndex) {
    if (!autoMode) {
        RelayState relayState;
        if (strcmp(message, "ON") == 0) {
            relayState = RELAY_ON;
        } else if (strcmp(message, "OFF") == 0) {
            relayState = RELAY_OFF;
        }
        toggleRelay(relayPin, relayIndex, relayState);
    }        
}

void handleTopLightCommand(const char* message) {
    if (!autoMode) {
        RelayState relayState;
        if (strcmp(message, "ON") == 0) {
            relayState = RELAY_ON;
        } else if (strcmp(message, "OFF") == 0) {
            relayState = RELAY_OFF;
        } 
        toggleRelay(relaysPins.topLight, TopL, relayState);
    }        
}

void handleBottomLightCommand(const char* message) {
    if (!autoMode) {
        RelayState relayState;
        if (strcmp(message, "ON") == 0) {
            relayState = RELAY_ON;
        } else if (strcmp(message, "OFF") == 0) {
            relayState = RELAY_OFF;
        }
        toggleRelay(relaysPins.bottomLight, BtmL, relayState);
    }    
}

void handleFanCommand(const char* message) {
    if (!autoMode) {
        RelayState relayState;
        if (strcmp(message, "ON") == 0) {
            relayState = RELAY_ON;
        } else if (strcmp(message, "OFF") == 0) {
            relayState = RELAY_OFF;
        }
        toggleRelay(relaysPins.fan, Fan, relayState);
    }    
}

void handlePumpCommand(const char* message) {
    if (!autoMode) {
        RelayState relayState;
        if (strcmp(message, "ON") == 0) {
            relayState = RELAY_ON;
        } else if (strcmp(message, "OFF") == 0) {
            relayState = RELAY_OFF;
        }
        toggleRelay(relaysPins.pump, Pump, relayState);
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