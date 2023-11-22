/*
 * pwm.h
 *
 *  Created on: Jul 24, 2022
 *      Author: MSI
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32f4xx_hal.h"

class Pwm
{
public:
	TIM_HandleTypeDef htim;
	uint32_t channel;
	float ofset = 0;

	Pwm()
	{
		this->channel = 0;
	}

	Pwm(TIM_HandleTypeDef _htim, uint32_t _channel, float _ofset)
	{
		this->htim = _htim;
		this->channel = _channel;
		this->ofset = _ofset;
		HAL_TIM_PWM_Start(&(this->htim), this->channel);
	}

	void SetAngle(float angle)
	{
		int duty = 500 + (angle + 90 + this->ofset) * (2000 / 180);
		__HAL_TIM_SetCompare(&this->htim, this->channel, duty);

	}
};

#endif /* INC_PWM_H_ */
