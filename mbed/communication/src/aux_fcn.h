#include <Arduino.h>

typedef union
{
  uint32_t Int;
  uint8_t  Byte[4];
  float Float;
}iTof;

uint8_t HexCharToByte(char hexChar);
uint8_t HexChar2ToByte(char upperVal, char lowerVal);
uint32_t HexChar8ToUint32(char hexChar7, char hexChar6, char hexChar5, char hexChar4, char hexChar3, char hexChar2, char hexChar1, char hexChar0);// 8 char degerini 4 byte cevirmek icin kullanilir
