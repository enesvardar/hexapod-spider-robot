#include <Arduino.h>

/**
  * @brief  Bu fonksiyon kendisine verilen bir hex karakterini uint8_t tipinde geri dondurur.
  * @param  hexChar
  * @retval value
  */
uint8_t HexCharToByte(char hexChar)
{
	uint8_t value;

	switch (hexChar)
	{

	case '0':
		value = 0x00;
		break;

	case '1':
		value = 0x01;
		break;

	case '2':
		value = 0x02;
		break;

	case '3':
		value = 0x03;
		break;

	case '4':
		value = 0x04;
		break;

	case '5':
		value = 0x05;
		break;

	case '6':
		value = 0x06;
		break;

	case '7':
		value = 0x07;
		break;

	case '8':
		value = 0x08;
		break;

	case '9':
		value = 0x09;
		break;

	case 'A':
		value = 0x0A;
		break;

	case 'B':
		value = 0x0B;
		break;

	case 'C':
		value = 0x0C;
		break;

	case 'D':
		value = 0x0D;
		break;

	case 'E':
		value = 0x0E;
		break;

	case 'F':
		value = 0x0F;
		break;

	default:
		// bu satir bilerek bos birakildi
		break;
	} // switch

	return value;
}

/**
  * @brief  Bu fonksiyon kendisine verilen 2 hex karakterini uint8_t tipinde geri dondurur.
  * @param  upperVal
  * @param  lowerVal
  * @retval uint8_t
  */
uint8_t HexChar2ToByte(char upperVal, char lowerVal)
{
	return ((HexCharToByte(upperVal) << 4) | HexCharToByte(lowerVal));
}


/**
  * @brief  Bu fonksiyon kendisine verilen 8 hex karakterini uint32_t tipinde geri dondurur.
  * @retval uint32_t
  */
uint32_t HexChar8ToUint32(char hexChar7, char hexChar6, char hexChar5, char hexChar4, char hexChar3, char hexChar2, char hexChar1, char hexChar0)
{
	uint32_t buf1 = 0x0000;
	uint32_t buf2 = 0x0000;


	buf1 = HexChar2ToByte(hexChar7, hexChar6);
	buf1 = buf1 << 8;
	buf1 = (buf1 | HexChar2ToByte(hexChar5, hexChar4));

	buf1 = buf1 << 16;

	buf2 = HexChar2ToByte(hexChar3, hexChar2);
	buf2 = buf2 << 8;
	buf2 = (buf2 | HexChar2ToByte(hexChar1, hexChar0));


	return buf1 | buf2;
}


void sendSerial(char* str){


}