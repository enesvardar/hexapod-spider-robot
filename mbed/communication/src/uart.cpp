
#include <SoftwareSerial.h>
#include "aux_fcn.h"
#include <myMqtt.h>

SoftwareSerial ESPserial(3, 1); // RX | TX
const unsigned int MAX_MESSAGE_LENGTH = 20;

void setupUart(void)
{

  // Start the software serial for communication with the ESP8266
  ESPserial.begin(115200);
}

void uartLoop(void)
{

  // Check to see if anything is available in the serial receive buffer
  while (ESPserial.available() > 0)
  {
    // Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    // Read the next available byte in the serial receive buffer
    char inByte = ESPserial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if (inByte != '/n' && message_pos < MAX_MESSAGE_LENGTH)
    {
      // Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    // Full message received...
    else
    {

      uint8_t checksum = 0;

      Serial.println(message);

      message_pos = 0;
    }
  }
}

enum Command_Type_t /* Komut mesajinin tipini tutan enum degiskeni*/
{
  Cmd_Go_Flash = 0x11,
  Cmd_Go_Forw = 0x01,
  Cmd_Go_Left = 0x02,
  Cmd_Go_Rote = 0x03,
  Cmd_Go_Rigt = 0x04,
  Cmd_Go_Back = 0x05,
  Cmd_Go_Stop = 0x06,
  Cmd_Step_Rx = 0x07,
  Cmd_Step_Ry = 0x08,
  Cmd_Step_Rz = 0x09,
  Cmd_Step_Tx = 0x0A,
  Cmd_Step_Ty = 0x0B,
  Cmd_Step_Tz = 0x0C,
  Cmd_Dance = 0x0D,
  Cmd_Balance = 0x0E,
  Cmd_Reset = 0x0F,
};

void sendCmd(uint8_t cmd, int8_t data)
{

  char str[7]; // gonderilcek mesaj
  memset(str, 0, 7);
  uint8_t checkSum = 0;
  uint8_t cmdN = cmd;
  checkSum = cmd + (uint8_t)data;
  checkSum = ~checkSum + 1;
  sprintf(str, ":%02X%02X%02X", cmdN, (uint8_t)data, checkSum);
  ESPserial.println(str);
}

void uartSend(String str)
{

  int msgTry = 0;

line:

  if (str == "flash")
  {
    sendCmd(Cmd_Go_Flash, 0);
  }
  if (str == "forw")
  {
    sendCmd(Cmd_Go_Forw, 0);
  }
  else if (str == "left")
  {
    sendCmd(Cmd_Go_Left, 0);
  }
  if (str == "rote")
  {
    sendCmd(Cmd_Go_Rote, 0);
  }
  else if (str == "rigt")
  {
    sendCmd(Cmd_Go_Rigt, 0);
  }
  else if (str == "back")
  {
    sendCmd(Cmd_Go_Back, 0);
  }
  else if (str == "stop")
  {
    sendCmd(Cmd_Go_Stop, 0);
  }
  else if (str == "reset")
  {
    sendCmd(Cmd_Reset, 0);
    Serial.println(str);
  }
  else if (str == "dance")
  {
    sendCmd(Cmd_Dance, 0);
    Serial.println(str);
  }
  else if (str == "balance")
  {
    sendCmd(Cmd_Balance, 0);
    Serial.println(str);
  }
  else if (str[0] == 'r' && str[1] == 'x')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Rx, dis);
  }
  else if (str[0] == 'r' && str[1] == 'y')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Ry, dis);
  }
  else if (str[0] == 'r' && str[1] == 'z')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Rz, dis);
  }
  else if (str[0] == 't' && str[1] == 'x')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Tx, dis);
  }
  else if (str[0] == 't' && str[1] == 'y')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Ty, dis);
  }
  else if (str[0] == 't' && str[1] == 'z')
  {

    char chr[4] = {str[2], str[3], str[4], str[5]};
    int dis = atoi(chr);
    sendCmd(Cmd_Step_Tz, dis);
  }

  int pin = 0;
  int cnt = 0;
  while (!pin && cnt < 100)
  {
    pin = digitalRead(5);
    cnt++;
    delay(1);
  }

  if (pin == 0 && msgTry < 3)
  {
    Serial.println(msgTry);
    msgTry++;
    goto line;
  }
}