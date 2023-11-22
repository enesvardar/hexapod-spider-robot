#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <uart.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

char *mqttServer = "broker.hivemq.com";
char *topicNameESP = "/spider/ESP32";
char *topicNameNODE = "/spider/NODEJS";
char *clientId = "spiderRobot-";
int mqttPort = 1883;

int Led = 1;

void callback(char *topic, byte *payload, unsigned int length)
{
    if (*topic == *topicNameESP){
    String msg = "";

    for (int i = 0; i < length; i++)
    {
      msg += ((char)payload[i]);
    }

    uartSend(msg);
    
    Led = not Led ;
    digitalWrite(2, Led);
  }
}

void reconnect()
{

  Serial.println("Connecting to MQTT Broker...");

  while (!mqttClient.connected())
  {

    Serial.println("Reconnecting to MQTT Broker..");
    String id = "spiderRobot-";
    id = clientId + String(random(0xffff), HEX);

    if (mqttClient.connect(id.c_str()))
    {
      Serial.println("Server Connected.");
      mqttClient.subscribe(topicNameESP);
    }
  }
}

void sendMqttData(char* data)
{ 
  mqttClient.publish(topicNameNODE, data);
}

void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);

  pinMode(2,OUTPUT);
}

