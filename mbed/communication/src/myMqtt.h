#include <Arduino.h>
#include <PubSubClient.h>

extern PubSubClient mqttClient;

void callback(char *topic, byte *payload, unsigned int length);
void setupMQTT();
void reconnect();
void sendMqttData(char* data);
