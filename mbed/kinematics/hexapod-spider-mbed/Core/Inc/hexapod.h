/*
 * hexapod.h
 *
 *  Created on: 24 Tem 2022
 *      Author: MSI
 */

#ifndef INC_HEXAPOD_H_
#define INC_HEXAPOD_H_

#include <globals.h>
#include "myMath.h"
#include "parameters.h"
#include <list>
#include "leg.h"
#include "stm32f4xx_hal.h"

/*

        (leftFront)       (rightFront)

                \   head  /
                 *---*---*
                /    |    \
               /     |     \
              /      |      \
 leftMiddle --*-----cog------*-- (rightMiddle)
              \      |      /
               \     |     /
                \    |    /
                 *---*---*
                /         \

           (leftBack)   (rightBack)

   leftBack,rightMiddle,leftFront == > LEG_GROUP.firstly
   rightBack,leftMiddle,rightFront == > LEG_GROUP.secondly
*/

class Hexapod
{
public:

	Leg legs[6] = {
			Leg("leftBack", myParameters.endOfset),
			Leg("leftMiddle", myParameters.endOfset),
			Leg("leftFront", myParameters.endOfset),
			Leg("rightBack", myParameters.endOfset),
			Leg("rightMiddle", myParameters.endOfset),
			Leg("rightFront", myParameters.endOfset)
	};

private:

	// yürüme, dönme ve dans adımlarını tutan değişkenler
	WalkingStep stepWalk;
	RotatingStep stepRotate;
	DancingStep stepDancing;

	int changePosY;
	float changeRotateZ;
	float A;

	float danceTheta;
	float danceX;
	float danceY;
	float bufDanceX;
	float bufDanceY;

public:

	MyVector3 bufBodyLocalPosition; // gövdesinin origine göre pozisyonunu tutan buffer
	MyVector3 bufBodyLocalEulerAngles; // gövdesinin origine göre açısal farkını tutan buffer

	Hexapod()
	{
		this->stepWalk = WalkingStep_Sleepy;
		this->stepRotate = RotatingStep_Sleepy;
		this->stepDancing = DancingStep_Sleepy;

		this->changePosY = 0;
		this->changeRotateZ = 0;
		this->A = 0;

		this->danceTheta = 0;
		this->danceX = 0;
		this->danceY = 0;
		this->bufDanceX = 0;
		this->bufDanceY = 0;
	};

private:

	// Bu fonkisyon robotun gövdesini hareket ettirmek için kullanılır.
	void MoveHexapodBodyDir(float step, Direction dir)
	{
		float PI = 3.14159265358979323846f;
		float stepX = 0;
		float stepY = 0;

		// gövedenin bulunduğu rotation bilgisini ve hareket ettirmilken isteninlen yöne göre x ve y eksenlerinde gidilecek step değerleri hesaplanıyor
		if (dir == Direction_Back || dir == Direction_Forward)
		{
			if (dir == Direction_Back)
			{
				step *= -1;
			}

			stepX = -sin(PI * myParameters.bodyLocalEulerAngles.z / 180) * step;

			stepY = cos(PI * myParameters.bodyLocalEulerAngles.z / 180) * step;
		}
		else if (dir == Direction_Right || dir == Direction_Left)
		{
			if (dir == Direction_Left)
			{
				step *= -1;
			}

			stepX = cos(PI * myParameters.bodyLocalEulerAngles.z / 180) * step;

			stepY = sin(PI * myParameters.bodyLocalEulerAngles.z / 180) * step;
		}

		myParameters.bodyLocalPosition = MyVector3(myParameters.bodyLocalPosition.x + stepX, myParameters.bodyLocalPosition.y + stepY, myParameters.bodyLocalPosition.z);
	}

public:
	// Bu fonksiyon robot gövdesini x y z ekseninde hareket ettirmek için kullanılır
	void MoveHexapodBodyXYZ(float stepX, float stepY, float stepZ)
	{
		myParameters.bodyLocalPosition = MyVector3(myParameters.bodyLocalPosition.x + stepX, myParameters.bodyLocalPosition.y + stepY, myParameters.bodyLocalPosition.z + stepZ);
	}

	// Bu fonksiyon robot gövdesini x y z ekseninde döndürmek ettirmek için kullanılır
	void RotateHexapodBodyXYZ(float stepX, float stepY, float stepZ)
	{
		myParameters.bodyLocalEulerAngles = MyVector3(myParameters.bodyLocalEulerAngles.x + stepX, myParameters.bodyLocalEulerAngles.y + stepY, myParameters.bodyLocalEulerAngles.z + stepZ);
	}

private:
	// BU fonksiyon ile gövde pozisyonu istenilen bir konuma set edilir
	void SetLocalPositionHexapodBody(MyVector3 value)
	{
		myParameters.bodyLocalPosition = value;
	}

	// BU fonksiyon ile gövde rotatini istenilen bir değere set edilir
	void SetLocalEulerAnglesHexapodBody(MyVector3 value)
	{
		myParameters.bodyLocalEulerAngles = value;
	}

	void MoveLegGroup(int group, int step, Direction dir)
	{
		for (int i = 0; i < step; i++)
		{
			switch (group)
			{
				case (int)LEG_GROUP_Firstly:
					legs[(int)(LEG_NAME_LeftBack)].MoveDirLegBasePoint(dir);
					legs[(int)(LEG_NAME_RightMiddle)].MoveDirLegBasePoint(dir);
					legs[(int)(LEG_NAME_LeftFront)].MoveDirLegBasePoint(dir);
					break;

				case (int)LEG_GROUP_Secondly:
					legs[(int)(LEG_NAME_RightBack)].MoveDirLegBasePoint(dir);
					legs[(int)(LEG_NAME_LeftMiddle)].MoveDirLegBasePoint(dir);
					legs[(int)(LEG_NAME_RightFront)].MoveDirLegBasePoint(dir);
					break;

				default:
					break;
			}
		}
	}

	bool WalkingSpecialStep(Direction dir, int group, int conditionY, double yaw, bool flashFlag)
	{
		bool done = false;

		if (changePosY < (conditionY / 2))
		{
			MoveLegGroup(group, 5, Direction_Up);
		}
		else
		{
			MoveLegGroup(group, 5, Direction_Down);
		}

		if(flashFlag == true)
		{
			if(yaw < 0)
			{
				RotateHexapodBodyXYZ(0, 0, -0.1f);
				RotateLegGroup(group, 0);
			}
			else if(0 > yaw)
			{
				RotateHexapodBodyXYZ(0, 0, +0.1f);
				RotateLegGroup(group, 0);
			}
		}

		MoveHexapodBodyDir(1, dir);
		MoveLegGroup(group,2, dir);

		changePosY++;

		if (changePosY == conditionY)
		{
			changePosY = 0;
			done = true;
		}

		return done;
	}

	void RotateLegGroup(int group,float rotateZ)
	{
		switch (group)
		{
			case (int)LEG_GROUP_Firstly:
				legs[LEG_NAME_LeftBack].UpdateLegBaseFORG(rotateZ);
				legs[LEG_NAME_RightMiddle].UpdateLegBaseFORG(rotateZ);
				legs[LEG_NAME_LeftFront].UpdateLegBaseFORG(rotateZ);
				break;

			case (int)LEG_GROUP_Secondly:
				legs[LEG_NAME_RightBack].UpdateLegBaseFORG(rotateZ);
				legs[LEG_NAME_LeftMiddle].UpdateLegBaseFORG(rotateZ);
				legs[LEG_NAME_RightFront].UpdateLegBaseFORG(rotateZ);
				break;

			default:
				break;
		}
	}

	bool RotatingSpecialStep(int group, float stepZ, float rotateZ, int condZ)
	{

		float PI = 3.14159f;
		float Rad2Deg = 180.0 / PI;

		bool done = false;

		RotateHexapodBodyXYZ(0, 0, stepZ);

		RotateLegGroup(group, rotateZ);

		if (changeRotateZ <= condZ)
		{
			MoveLegGroup(group, 15, Direction_Up);
		}
		else
		{
			MoveLegGroup(group, 15, Direction_Down);
		}

		if (changeRotateZ ==  (2 * condZ))
		{
			done = true;
			changeRotateZ = 0;

			if (group == LEG_GROUP_Firstly)
				A = fmod(legs[LEG_NAME_RightFront].alphaAngleRad * Rad2Deg, 360);
			else
				A = fmod(legs[LEG_NAME_LeftFront].alphaAngleRad * Rad2Deg, 360);
		}

		HAL_Delay(8); // 2sn

		return done;
	}

public:

	void Walking(Direction dir, bool contFlag , double yaw, bool flashFlag)
	{
		bool done = false;

		switch (stepWalk)
		{
			case WalkingStep_Sleepy:
				stepWalk = contFlag == true ? WalkingStep_Start : stepWalk;
				break;
			case WalkingStep_Start:
				done = WalkingSpecialStep(dir, (int)LEG_GROUP_Firstly, 30 , yaw, flashFlag);
				stepWalk = done == true ? WalkingStep_Walking2 : stepWalk;
				break;
			case WalkingStep_Walking1:

				done = WalkingSpecialStep(dir, (int)LEG_GROUP_Firstly, 60, yaw, flashFlag);
				stepWalk = done == true ? WalkingStep_Walking2 : stepWalk;
				if (done == true)
					stepWalk = contFlag == false ? WalkingStep_Stop : stepWalk;
				break;

			case WalkingStep_Walking2:

				done = WalkingSpecialStep(dir, (int)LEG_GROUP_Secondly, 60, yaw, flashFlag);
				stepWalk = done == true ? WalkingStep_Walking1 : stepWalk;
				break;

			case WalkingStep_Stop:
				done = WalkingSpecialStep(dir, (int)LEG_GROUP_Secondly, 30, yaw, flashFlag);
				stepWalk = done == true ? WalkingStep_Sleepy : stepWalk;
				break;
			default:
				break;
		}
	}

	void Rotating(bool contFlag)
	{
		bool done = false;

		switch (stepRotate)
		{
			case RotatingStep_Sleepy:
				stepRotate = contFlag == true ? RotatingStep_Start : stepRotate;
				break;
			case RotatingStep_Start:
				changeRotateZ = changeRotateZ + 1;
				done = RotatingSpecialStep((int)LEG_GROUP_Firstly, 1, changeRotateZ, 10);
				stepRotate = done == true ? RotatingStep_Rotating1 : stepRotate;
				break;
			case RotatingStep_Rotating1:
				changeRotateZ = changeRotateZ + 0.5f;
				done = RotatingSpecialStep((int)LEG_GROUP_Secondly, 0.5f, A + (20 - A) * changeRotateZ / 20, 10);
				stepRotate = done == true ? RotatingStep_Rotating2 : stepRotate;
				break;
			case RotatingStep_Rotating2:
				changeRotateZ = changeRotateZ + 0.5f;
				done = RotatingSpecialStep((int)LEG_GROUP_Firstly, 0.5f, A + (20 - A) * changeRotateZ / 20, 10);
				stepRotate = done == true ? RotatingStep_Rotating1 : stepRotate;
				if (done == true)
					stepRotate = contFlag == false ? RotatingStep_Stop : stepRotate;
				break;
			case RotatingStep_Stop:
				changeRotateZ = changeRotateZ + 0.5f;
				done = RotatingSpecialStep((int)LEG_GROUP_Secondly, 0.5f, A + (-A) * changeRotateZ / 10, 5);
				stepRotate = done == true ? RotatingStep_Sleepy : stepRotate;
				break;
			default:
				break;
		}
	}

	void Dancing(bool contFlag)
	{
		float PI = 3.14159265358979323846f;
		float Deg2Rad = PI / 180.f;

		switch (stepDancing)
		{
			case DancingStep_Sleepy:

				bufBodyLocalPosition = myParameters.bodyLocalPosition;
				bufBodyLocalEulerAngles = myParameters.bodyLocalEulerAngles;
				stepDancing = contFlag == true ? DancingStep_Dancing : stepDancing;

				break;

			case DancingStep_Dancing:

				danceTheta++;
				danceX = (float)cos(Deg2Rad * danceTheta);
				danceY = (float)sin(Deg2Rad * danceTheta);
				MoveHexapodBodyXYZ((danceX - bufDanceX) * 30, (danceY - bufDanceY) * 30, 0);
				RotateHexapodBodyXYZ((danceX - bufDanceX) * 5, (danceY - bufDanceY) * 5, 0);
				bufDanceX = danceX;
				bufDanceY = danceY;
				stepDancing = contFlag == false ? DancingStep_Stop : stepDancing;

				break;

			case DancingStep_Stop:

				MyVector3 difPos = myParameters.bodyLocalPosition - bufBodyLocalPosition;
				MyVector3 difAngle = myParameters.bodyLocalEulerAngles - bufBodyLocalEulerAngles;

				if (abs(difPos.x) < 1 && abs(difAngle.x) < 1)
				{
					danceTheta = 0;
					stepDancing = DancingStep_Sleepy;

					SetLocalPositionHexapodBody(bufBodyLocalPosition);
					SetLocalEulerAnglesHexapodBody(bufBodyLocalEulerAngles);

					bufDanceX = 0;
					bufDanceY = 0;
				}
				else
				{
					MoveHexapodBodyXYZ(-difPos.x / 100, -difPos.y / 100, 0);
					RotateHexapodBodyXYZ(-difAngle.x / 100, -difAngle.y / 100, 0);
				}

				break;
		}
	}

	void Balancing(bool balanceFlag, double theta, double gama)
	{
		static int cntMPU = 0;

		static float bufGama = 0;
		static float bufTheta = 0;

		if(balanceFlag == true){

			cntMPU++;

			if(cntMPU == 10)
			{
				cntMPU = 0;

				if (abs(gama) > 0.1){
					//RotateHexapodBodyXYZ(0.1*gama, 0, 0);
					RotateHexapodBodyXYZ(0.1*gama + 1*(bufGama - gama), 0, 0);
				}

				if (abs(theta) > 0.1){
					//RotateHexapodBodyXYZ(0, 0.1*theta, 0);
					RotateHexapodBodyXYZ(0, 0.1*theta + 1*(bufTheta - theta), 0);
				}
			}

			bufGama = gama;
			bufTheta = theta;
		}
	}


	float Update()
	{
		float delay = 0;

		for(int i = 0; i < 6; i++){

			if(legs[i].delayTime > delay)
			{
				delay = legs[i].delayTime;
			}
		}


		legs[0].Update();
		legs[1].Update();
		legs[2].Update();
		legs[3].Update();
		legs[4].Update();
		legs[5].Update();


		//HAL_Delay(delay);

		return delay;
	}

};

#endif /* INC_HEXAPOD_H_ */
