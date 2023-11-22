/*
 * parameters.h
 *
 *  Created on: Jul 23, 2022
 *      Author: MSI
 */

#ifndef SRC_PARAMETERS_PARAMETERS_H_
#define SRC_PARAMETERS_PARAMETERS_H_

#include "math.h"
#include "myMath.h"

class Parameters {
public:
	float coxia;
	float tibiaX;
	float tibiaH;
	float femuarX;
	float femuarH;
	float endOfset;

	MyVector3 bodyLocalEulerAngles;
	MyVector3 bodyLocalPosition;

	float lenght;

	MyVector3 lbEulerAngles;// left back
	MyVector3 lmEulerAngles;// left middle
	MyVector3 lfEulerAngles;// left front
	MyVector3 rbEulerAngles;// right back
	MyVector3 rmEulerAngles;// right middle
	MyVector3 rfEulerAngles;// right front

	// ContactCenterPoint => ContCntrPnt

	MyVector3 lbContCntrPnt;
	MyVector3 lmContCntrPnt;
	MyVector3 lfContCntrPnt;
	MyVector3 rbContCntrPnt;
	MyVector3 rmContCntrPnt;
	MyVector3 rfContCntrPnt;

	// For Orgin
	MyVector3 lbLegBaseFORG;
	MyVector3 lmLegBaseFORG;
	MyVector3 lfLegBaseFORG;
	MyVector3 rbLegBaseFORG;
	MyVector3 rmLegBaseFORG;
	MyVector3 rfLegBaseFORG;

	Parameters()
	{
		float PI = 3.14159265358979323846f;

		this->coxia = 45;
		this->tibiaX = 56;
		this->tibiaH = 18;
		this->femuarX = 0;
		this->femuarH = 90;

		this->endOfset = 0;

		this->bodyLocalEulerAngles = MyVector3(0, 0, 0);
		this->bodyLocalPosition = MyVector3(0, 0, 70);

		this->lenght = coxia + tibiaX + femuarX;

		this->lbEulerAngles = MyVector3(0, 0, 120);// left back
		this->lmEulerAngles = MyVector3(0, 0, 180);// left middle
		this->lfEulerAngles = MyVector3(0, 0, 240);// left front
		this->rbEulerAngles = MyVector3(0, 0, 60); // right back
		this->rmEulerAngles = MyVector3(0, 0, 360);// right middle
		this->rfEulerAngles = MyVector3(0, 0, 300);// right front

		// ContactCenterPoint => ContCntrPnt
		this->lbContCntrPnt = MyVector3(-68, 120.0f, 0);
		this->lmContCntrPnt = MyVector3(-140, 0, 0);
		this->lfContCntrPnt = MyVector3(-68, -120.0f, 0);
		this->rbContCntrPnt = MyVector3(68, 120.0f, 0);
		this->rmContCntrPnt = MyVector3(140, 0, 0);
		this->rfContCntrPnt = MyVector3(68, -120.0f, 0);

        // For Orgin
		this->lbLegBaseFORG = this->lbContCntrPnt + MyVector3(cos(PI * this->lbEulerAngles.z / 180) * lenght, sin(PI * this->lbEulerAngles.z / 180) * lenght, 0);
		this->lmLegBaseFORG = this->lmContCntrPnt + MyVector3(cos(PI * this->lmEulerAngles.z / 180) * lenght, sin(PI * this->lmEulerAngles.z / 180) * lenght, 0);
		this->lfLegBaseFORG = this->lfContCntrPnt + MyVector3(cos(PI * this->lfEulerAngles.z / 180) * lenght, sin(PI * this->lfEulerAngles.z / 180) * lenght, 0);
		this->rbLegBaseFORG = this->rbContCntrPnt + MyVector3(cos(PI * this->rbEulerAngles.z / 180) * lenght, sin(PI * this->rbEulerAngles.z / 180) * lenght, 0);
		this->rmLegBaseFORG = this->rmContCntrPnt + MyVector3(cos(PI * this->rmEulerAngles.z / 180) * lenght, sin(PI * this->rmEulerAngles.z / 180) * lenght, 0);
		this->rfLegBaseFORG = this->rfContCntrPnt + MyVector3(cos(PI * this->rfEulerAngles.z / 180) * lenght, sin(PI * this->rfEulerAngles.z / 180) * lenght, 0);
	};
};

extern Parameters myParameters;

#endif /* SRC_PARAMETERS_PARAMETERS_H_ */
