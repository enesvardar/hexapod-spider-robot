/*
 * msg.h
 *
 *  Created on: 10 Kas 2022
 *      Author: MSI
 */

#ifndef INC_MSG_H_
#define INC_MSG_H_

#include "stdint.h"
#include "stdbool.h"
#include "math.h" // Standart C Lib Header
#include "stdlib.h" // Standart C Lib Header
#include "stdio.h" // Standart C Lib Header

typedef union
{
  uint32_t Int;
  uint8_t  Byte[4];
  float Float;
}iTof;

enum Command_Type_t/* Komut mesajinin tipini tutan enum degiskeni*/
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

typedef enum Command_Type_t Command_Type_t;


struct Message_t /* Gelen bir mesajin bilgilerini tutan struct */
{
	Command_Type_t type; /* tip*/
	uint16_t adress; /* adres bilgisi */
	int8_t data; /* data bilgisi */
	uint8_t checkSum; /* checksum */
	bool accuracy; /* dogrulugu */
};

typedef struct Message_t Message_t;

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


Message_t Message_Parser(char *chrHexLine)
{

	Message_t msg;

	msg.checkSum = 0x00;

	msg.type = (Command_Type_t)HexChar2ToByte(chrHexLine[1], chrHexLine[2]);

	/*  checSum hesaplamasi yapiliyor */
	msg.checkSum = HexChar2ToByte(chrHexLine[1], chrHexLine[2]);
	msg.checkSum = HexChar2ToByte(chrHexLine[3], chrHexLine[4]) + msg.checkSum;
	msg.checkSum = ~msg.checkSum + 0x01;

	/* hesaplanan checkSum degeri ile mesaj olarak gelen checksum karsilastiriliyor */
	if (msg.checkSum == HexChar2ToByte(chrHexLine[5], chrHexLine[6]))
	{

		if(msg.type > 6){
			msg.data = (int8_t)HexChar2ToByte(chrHexLine[3], chrHexLine[4]);
		}

		msg.accuracy = true;
	}
	else
	{
		msg.accuracy = false;
	}

	return msg;
}



#endif /* INC_MSG_H_ */
