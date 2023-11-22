#include <Arduino.h>
#include <WiFi.h>

//const char *SSID = "Kablonet Netmaster-8584-G";
//const char *PWD = "16642429";

const char *SSID = "iPhone";
const char *PWD = "16642429";

void connectToWiFi()
{
  Serial.print("Connectiog to ");

  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.");

  digitalWrite(2, 1);
}
