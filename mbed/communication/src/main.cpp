
#include <Arduino.h>
#include <myWifi.h>
#include <myMqtt.h>
#include <uart.h>

void setup()
{
  pinMode(5, INPUT);
  Serial.begin(9600);
  connectToWiFi();
  setupMQTT();
  setupUart();
}

void loop()
{
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
}
