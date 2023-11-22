/*
 * gloabals.h
 *
 *  Created on: 24 Tem 2022
 *      Author: MSI
 */

#ifndef SRC_GLOBALS_GLOABALS_H_
#define SRC_GLOBALS_GLOABALS_H_

#include "stm32f4xx_hal.h"
#include <hexapod.h>

enum LEG_NAME : int
{
   LEG_NAME_LeftBack = 0,
   LEG_NAME_LeftMiddle = 1,
   LEG_NAME_LeftFront = 2,
   LEG_NAME_RightBack = 3,
   LEG_NAME_RightMiddle = 4,
   LEG_NAME_RightFront = 5,
};

enum LEG_GROUP : int
{
	LEG_GROUP_Firstly = 1,
	LEG_GROUP_Secondly = 2,
};

enum Direction
{
	Direction_Forward,
	Direction_Back,
	Direction_Up,
	Direction_Down,
	Direction_Left,
	Direction_Right,
	Direction_None
};

enum WalkingStep
{
	WalkingStep_Sleepy,
	WalkingStep_Start,
	WalkingStep_Walking1,
	WalkingStep_Walking2,
	WalkingStep_Stop
};

enum RotatingStep
{
	RotatingStep_Sleepy,
	RotatingStep_Start,
	RotatingStep_Rotating1,
	RotatingStep_Rotating2,
	RotatingStep_Stop
};

enum DancingStep
{
	DancingStep_Sleepy,
	DancingStep_Dancing,
	DancingStep_Stop
};

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim9;

#endif /* SRC_GLOBALS_GLOABALS_H_ */
