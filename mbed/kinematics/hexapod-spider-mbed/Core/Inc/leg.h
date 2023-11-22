/*
 * leg.h
 *
 *  Created on: 24 Tem 2022
 *      Author: MSI
 */

#ifndef SRC_LEG_LEG_H_
#define SRC_LEG_LEG_H_

#include <globals.h>
#include <iostream>
#include <string>
#include <math.h>
#include "myMath.h"
#include "parameters.h"
#include "pwm.h"

using namespace std;

Parameters myParameters = Parameters();


class Leg
{
public:

	MyVector3 legBaseFORG; // bacak tabanın orgindeki kordinat sistemine göre pozisyonu
	MyVector3 legBaseFCCP; // bacak tabanın bacağın gövdeye bağlandığı yerdeki kordinat sistemine göre pozisyonu
	MyVector3 legCCP; // bacağın gövdeye bağlandığı noktadaki kordinat sistemininin, gövdedeki kordinat sitemine göre pozisyonu
	MyVector3 legLocalEulerAngles; // bacağın gövdeye bağlandığı noktadaki kordinat sistemininin, gövdedeki kordinat sitemine göre açısal konumu

	Pwm alphaIO;
	Pwm betaIO;
	Pwm gamaIO;

	float alphaAngleRad; // alpha açısının radyan değeri
	float betaAngleRad; // beta açısının radyan değeri
	float gamaAngleRad; // gama açısının radyan değeri

	float preAlphaAngleDeg; // alpha açısının radyan değeri
	float preBetaAngleDeg; // beta açısının radyan değeri
	float preGamaAngleDeg; // gama açısının radyan değeri

	float delayTime;

	string name; // her bir bacağın isminin tutulduğu değişken (leftBack,leftMiddle....rightFront)

	Leg(string _name, float _endOfset)
	{
		this->alphaAngleRad = 0; // alpha açısının radyan değeri
		this->betaAngleRad = 0; // beta açısının radyan değeri
		this->gamaAngleRad = 0; // gama açısının radyan değeri

		this->preAlphaAngleDeg  = 0; // alpha açısının radyan değeri
		this->preBetaAngleDeg = 0; // beta açısının radyan değeri
		this->preGamaAngleDeg = 0; // gama açısının radyan değeri

		this->delayTime = 0;

		// bacağın ismi okunuyor
		name = _name;

		// parametreden her bacağın parametreleri okuyor

		if (name == "leftBack")
		{
			this->legLocalEulerAngles = myParameters.lbEulerAngles;
			this->legBaseFORG = myParameters.lbLegBaseFORG;
			this->legCCP = myParameters.lbContCntrPnt;

			this->alphaIO = Pwm(htim8, TIM_CHANNEL_1, 0);
			this->betaIO = Pwm(htim8, TIM_CHANNEL_3, 0);
			this->gamaIO = Pwm(htim8, TIM_CHANNEL_2, 0);
		}
		else if (name == "leftMiddle")
		{
			this->legLocalEulerAngles = myParameters.lmEulerAngles;
			this->legBaseFORG = myParameters.lmLegBaseFORG;
			this->legCCP = myParameters.lmContCntrPnt;

			this->alphaIO = Pwm(htim4, TIM_CHANNEL_2, 0);
			this->betaIO = Pwm(htim4, TIM_CHANNEL_1, 0);
			this->gamaIO = Pwm(htim2, TIM_CHANNEL_2, 0);
		}
		else if (name == "leftFront")
		{
			this->legLocalEulerAngles = myParameters.lfEulerAngles;
			this->legBaseFORG = myParameters.lfLegBaseFORG;
			this->legCCP = myParameters.lfContCntrPnt;

			this->alphaIO = Pwm(htim4, TIM_CHANNEL_4, 0);
			this->betaIO = Pwm(htim4, TIM_CHANNEL_3, 0);
			this->gamaIO = Pwm(htim9, TIM_CHANNEL_1, 0);

		}
		else if (name == "rightBack")
		{
			this->legLocalEulerAngles = myParameters.rbEulerAngles;
			this->legBaseFORG = myParameters.rbLegBaseFORG;
			this->legCCP = myParameters.rbContCntrPnt;

			this->alphaIO = Pwm(htim1, TIM_CHANNEL_4, 0);
			this->betaIO = Pwm(htim12, TIM_CHANNEL_1, 0);
			this->gamaIO = Pwm(htim12, TIM_CHANNEL_2, 0);
		}
		else if (name == "rightMiddle")
		{
			this->legLocalEulerAngles = myParameters.rmEulerAngles;
			this->legBaseFORG = myParameters.rmLegBaseFORG;
			this->legCCP = myParameters.rmContCntrPnt;

			this->alphaIO = Pwm(htim3, TIM_CHANNEL_3, 0);
			this->betaIO = Pwm(htim1, TIM_CHANNEL_1, 0);
			this->gamaIO = Pwm(htim1, TIM_CHANNEL_2, 0);
		}
		else if (name == "rightFront")
		{
			this->legLocalEulerAngles = myParameters.rfEulerAngles;
			this->legBaseFORG = myParameters.rfLegBaseFORG;
			this->legCCP = myParameters.rfContCntrPnt;

			this->alphaIO = Pwm(htim2, TIM_CHANNEL_1, 0);
			this->betaIO = Pwm(htim2, TIM_CHANNEL_3, 0);
			this->gamaIO = Pwm(htim3, TIM_CHANNEL_2, 0);

		}

		this->alphaIO.SetAngle(0);
		this->betaIO.SetAngle(0);
		this->gamaIO.SetAngle(0);

		// her bir bacağın ayak tabanı _endOfset değerine göre bir ofset kadar kaydırlıyor

		float _endOfsetX = 0;
		float _endOfsetY = 0;

		if((int)this->legBaseFORG.x > 0)
		{
			_endOfsetX = _endOfset * -1;
		}
		else
		{
			_endOfsetX = _endOfset;
		}

		if((int)this->legBaseFORG.y < 0)
		{
			_endOfsetX /= 2;
			_endOfsetY = _endOfset/2;
		}
		else if((int)this->legBaseFORG.y > 0)
		{
			_endOfsetX /= 2;
			_endOfsetY = (_endOfset / 2) * -1;
		}

		this->legBaseFORG = MyVector3(this->legBaseFORG.x + _endOfsetX, this->legBaseFORG.y +_endOfsetY, this->legBaseFORG.z);

		this->InverseKinematicsForLegBase();

		ForwardKinematicsForLegBase();
	}

	// Bu fonksiyon ile her bir bacak tabanın pozisyon bilgisi bacağın ana kordinat sistemine göre Q1,Q2 ve Q3 açıları ile güncellenmesini sağlar.
	void ForwardKinematicsForLegBase()
	{
		float Q1 = alphaAngleRad;
		float Q2 = betaAngleRad;
		float Q3 = gamaAngleRad;

		float px = (float)(cos(Q1) * (myParameters.coxia + myParameters.femuarX * cos(Q2 + Q3) - 1.0 * myParameters.femuarH * sin(Q2 + Q3) + myParameters.tibiaX * cos(Q2) - myParameters.tibiaH * sin(Q2)));
		float py = (float)(sin(Q1) * (myParameters.coxia + myParameters.femuarX * cos(Q2 + Q3) - 1.0 * myParameters.femuarH * sin(Q2 + Q3) + myParameters.tibiaX * cos(Q2) - myParameters.tibiaH * sin(Q2)));
		float pz = -myParameters.femuarH * cos(Q2 + Q3) - myParameters.femuarX * sin(Q2 + Q3) - myParameters.tibiaH * cos(Q2) - myParameters.tibiaX * sin(Q2);

		legBaseFCCP = MyVector3(px, py, pz);
	}

	// Bu fonksiyon ile bacağın ana koordinat sistemine göre bacak tabanın pozisyonu için gerekli  Q1,Q2 ve Q3 deperleri bulunur
	void InverseKinematicsForLegBase()
	{

		// ilk olarak dönme matrisi oluşturuluyor. Bacağın ana kordinat sisteminin orijine göre x , y ve z eksenlerinde dönme açıları hesaplanıyor
		MyQuaternion rotation = MyQuaternion();
		rotation.EulertoQuaternion(MyVector3(legLocalEulerAngles.x + myParameters.bodyLocalEulerAngles.x,
				legLocalEulerAngles.y + myParameters.bodyLocalEulerAngles.y, legLocalEulerAngles.z + myParameters.bodyLocalEulerAngles.z));

		// birim dönüşüm matrisi oluşturuluyor
		MyMatrix4x4 T = MyMatrix4x4();

		// dönüşüm matirisi oluşturulan dönme matrisi ile döndürülüyor
		T.Rotate(rotation);

		// bacağın ana kordinat sisteminin pozisyon değeri orijine göre okunuyor
		MyVector4 alphaPosForOrigin = GetAlphaPosForOrigin();

		// dönüşüm matrisine pozisyon değerleride girilerek, dönüşüm matrisi tamamlanıyor
		T.m03 = alphaPosForOrigin.x;
		T.m13 = alphaPosForOrigin.y;
		T.m23 = alphaPosForOrigin.z;

		/*
		 *  bacağın ana eksenine M, origine O diyelim.
		 *  bacak tabanının origine göre pozisyonu Op, bacağın ana eksenine göre pozisyonuna Mp diyelim
		 *                                                                      O
		 *   Dolayısıyla T dönüşüm matrisi O nun M ye göre durumunu tutuar       T   dir
		 *                                                                      M
		 *           O
		 *   Op =     T * Mp dir.
		 *           M
		 *
		 *   Biz Mp yi bulmak istediğimiz için dönüşüm matrisinin tersini alıyoruz.
		 *
		 *
		 *           M
		 *   Mp =     T * Op dir.
		 *           O
		 *
		 */

		T.Inverse();

		// bacağın ana eksenine göre pozisyonu aşağıdaki çarpım işlemi ile bulunuyor
		MyVector4 P = T * MyVector4(legBaseFORG.x, legBaseFORG.y, legBaseFORG.z, 1.0f);

		// ters kinematik denklemleri kullanılarak alpha beta gama açı değerleri hesaplanıyor.
		// kinematik denklemlerin çıkartılma şekli dokumantosyan adlı dosyadaki ppt açıklandı. Hesaplamalarda D-H tablosu kullanılıyor
		alphaAngleRad = atan2(P.y, P.x);

		float K = P.x * cos(alphaAngleRad) - myParameters.coxia + P.y * sin(alphaAngleRad);

		float a = (2 * K * myParameters.tibiaH + 2 * P.z * myParameters.tibiaX);
		float b = (-2 * K * myParameters.tibiaX + 2 * P.z * myParameters.tibiaH); ;
		float c = myParameters.femuarH * myParameters.femuarH + myParameters.femuarX * myParameters.femuarX - K * K - P.z * P.z - myParameters.tibiaH * myParameters.tibiaH - myParameters.tibiaX * myParameters.tibiaX;

		betaAngleRad = atan2(a, b) + atan2(sqrt(a * a + b * b - c * c), c);

		a = myParameters.femuarX;
		b = myParameters.femuarH;
		c = myParameters.coxia * sin(betaAngleRad) - P.z * cos(betaAngleRad) - P.x * cos(alphaAngleRad) * sin(betaAngleRad) - P.y * sin(alphaAngleRad) * sin(betaAngleRad) - myParameters.tibiaH;

		float gamaAngleX[2] = { 0, 0 };

		gamaAngleX[0] = atan2(a, b) + atan2(sqrt(a * a + b * b - c * c), c);
		gamaAngleX[1] = atan2(a, b) - atan2(sqrt(a * a + b * b - c * c), c);

		float dif[2] = { 0, 0 };

		for (int i = 0; i < 2; i++)
		{

			float px = cos(alphaAngleRad) * (myParameters.coxia + myParameters.femuarX * cos(betaAngleRad + gamaAngleX[i]) - myParameters.femuarH * sin(betaAngleRad + gamaAngleX[i]) + myParameters.tibiaX * cos(betaAngleRad) - myParameters.tibiaH * sin(betaAngleRad));
			float py = sin(alphaAngleRad) * (myParameters.coxia + myParameters.femuarX * cos(betaAngleRad + gamaAngleX[i]) - myParameters.femuarH * sin(betaAngleRad + gamaAngleX[i]) + myParameters.tibiaX * cos(betaAngleRad) - myParameters.tibiaH * sin(betaAngleRad));
			float pz = -myParameters.femuarH * cos(betaAngleRad + gamaAngleX[i]) - myParameters.femuarX * sin(betaAngleRad + gamaAngleX[i]) - myParameters.tibiaH * cos(betaAngleRad) - myParameters.tibiaX * sin(betaAngleRad);

			dif[i] = sqrt((px - P.x) * (px - P.x) + (py - P.y) * (py - P.y) + (pz - P.z) * (pz - P.z));
		}

		if (dif[0] <= dif[1])
		{
			gamaAngleRad = gamaAngleX[0];
		}
		else
		{
			gamaAngleRad = gamaAngleX[1];
		}
	}

	// Bu fonkisyon ile bacağın ana ekseninin ( bacağın gövdeye bağlandığı yerdeki eksen) origine göre pozisyon bilgsi okunuyor
	MyVector4 GetAlphaPosForOrigin()
	{
		// gövdenin origine göre dönüş matrisi oluşturuluyor
		MyQuaternion rotation = MyQuaternion();
		rotation.EulertoQuaternion(MyVector3(myParameters.bodyLocalEulerAngles.x, myParameters.bodyLocalEulerAngles.y, myParameters.bodyLocalEulerAngles.z));

		// birim dönüşüm matrisi oluşturuluyor
		MyMatrix4x4 T = MyMatrix4x4();

		// döünüşüm matirisi dönme matrisi ile döndürülüyor
		T.Rotate(rotation);

		// dönüşüm matrisine robot gövdesinin origine göre konum değerleri giriliyor
		T.m03 = myParameters.bodyLocalPosition.x;
		T.m13 = myParameters.bodyLocalPosition.y;
		T.m23 = myParameters.bodyLocalPosition.z;

		// bacağın ana ekseninin pozisyon değeri gövde deki kordinat sistemi için hesaplanıyor

		return T * MyVector4(legCCP.x, legCCP.y, legCCP.z, 1.0f);
	}

	void UpdateLegBaseFORG(float ofsetZ)
	{
		MyQuaternion rotation = MyQuaternion();
		rotation.EulertoQuaternion(MyVector3(legLocalEulerAngles.x + myParameters.bodyLocalEulerAngles.x, legLocalEulerAngles.y + myParameters.bodyLocalEulerAngles.y, legLocalEulerAngles.z + myParameters.bodyLocalEulerAngles.z + ofsetZ));

		MyMatrix4x4 T = MyMatrix4x4();

		T.Rotate(rotation);

		MyVector4 alphaPosForOrigin = GetAlphaPosForOrigin();

		T.m03 = alphaPosForOrigin.x;
		T.m13 = alphaPosForOrigin.y;
		T.m23 = alphaPosForOrigin.z;

		MyVector4 trans = T * MyVector4(legBaseFCCP.x, legBaseFCCP.y, legBaseFCCP.z, 1.0f);

		legBaseFORG = MyVector3(trans.x, trans.y, legBaseFORG.z);
	}

	// Bu fonkisyon ile bacak tabanı pozisyonu ofset değerleri kadar hareket ettirilir.
	void MoveLegBasePoint(float _endOfsetX, float _endOfsetY, float _endOfsetZ)
	{
		float PI = 3.14159f;
		float endOfsetX = 0;
		float endOfsetY = 0;

		if (_endOfsetY != 0)
		{
			endOfsetX = -sin(PI * myParameters.bodyLocalEulerAngles.z / 180) * _endOfsetY;

			endOfsetY = cos(PI * myParameters.bodyLocalEulerAngles.z / 180) * _endOfsetY;
		}
		else if (_endOfsetX != 0)
		{

			endOfsetX = cos(PI * myParameters.bodyLocalEulerAngles.z / 180) * _endOfsetX;

			endOfsetY = sin(PI * myParameters.bodyLocalEulerAngles.z / 180) * _endOfsetX;
		}

		legBaseFORG = MyVector3(legBaseFORG.x + endOfsetX, legBaseFORG.y + endOfsetY, legBaseFORG.z + _endOfsetZ);
	}

	// Bu fonksiyon ile bacak tabanı noktası istenilen yönlerde sahip olduğu birim hareket kabiliyeti kadar hareket eder.
	void MoveDirLegBasePoint(Direction dir)
	{
		switch (dir)
		{
			case Direction_Forward:
				MoveLegBasePoint(0, 1, 0);
				break;
			case Direction_Back:
				MoveLegBasePoint(0, -1, 0);
				break;
			case Direction_Up:
				MoveLegBasePoint(0, 0, 0.2f);
				break;
			case Direction_Down:
				MoveLegBasePoint(0, 0, -0.2f);
				break;
			case Direction_Left:
				MoveLegBasePoint(-1, 0, 0);
				break;
			case Direction_Right:
				MoveLegBasePoint(+1, 0, 0);
				break;
			case Direction_None:
				break;
			default:
				break;
		}
	}

	void Update() // Bu fonksiyon ile alpha beta ve gama açıları ile ilgili objeler hareket ettirliyor
	{
		float alphaAngleDeg = 0; // alpha açısının radyan değeri
		float betaAngleDeg = 0; // beta açısının radyan değeri
		float gamaAngleDeg = 0; // gama açısının radyan değeri

		float disAlphaAngleDeg = 0; // alpha açısının radyan değeri
		float disBetaAngleDeg = 0; // beta açısının radyan değeri
		float disGamaAngleDeg = 0; // gama açısının radyan değeri

		float maxDis = 0;

		float PI = 3.14159f;
		float Rad2Deg = 180.0 / PI;

		this->InverseKinematicsForLegBase(); // aci degerleri ters kinematik ile hesaplaniyor

		alphaAngleDeg = this->alphaAngleRad * Rad2Deg;
		betaAngleDeg = -this->betaAngleRad * Rad2Deg;
		gamaAngleDeg = this->gamaAngleRad * Rad2Deg;

		alphaAngleDeg = fmod (alphaAngleDeg, 360);
		betaAngleDeg = fmod (betaAngleDeg, 360);
		gamaAngleDeg = fmod (gamaAngleDeg, 360);

		if(alphaAngleDeg < -180){
			alphaAngleDeg += 360;
		}
		else if(alphaAngleDeg > +180){
			alphaAngleDeg -= 360;
		}

		if(betaAngleDeg < -180){
			betaAngleDeg += 360;
		}
		else if(betaAngleDeg > +180){
			betaAngleDeg -= 360;
		}

		if(betaAngleDeg > 80){
			betaAngleDeg = 80;
		}

		if(gamaAngleDeg < -180){
			gamaAngleDeg += 360;
		}
		else if(gamaAngleDeg > +180){
			gamaAngleDeg -= 360;
		}

		if(gamaAngleDeg > 135){
			gamaAngleDeg = 135;
		}

		if (alphaAngleDeg >= -360 && 360 > alphaAngleDeg &&
			betaAngleDeg >= -360 && 360 > betaAngleDeg &&
			gamaAngleDeg >= -360 && 360 > gamaAngleDeg)
		{

			this->alphaIO.SetAngle(-alphaAngleDeg);
			this->betaIO.SetAngle(-betaAngleDeg);
			this->gamaIO.SetAngle(-gamaAngleDeg);

			// Dampen towards the target rotation
			/*
			alpha.localRotation = Quaternion.Lerp(alpha.localRotation, Quaternion.Euler(0, 0, alphaAngleDeg), Time.deltaTime * 100);
			beta.localRotation = Quaternion.Lerp(beta.localRotation, Quaternion.Euler(new Vector3(90, 0, betaAngleDeg)), Time.deltaTime * 100);
			gama.localRotation = Quaternion.Lerp(gama.localRotation, Quaternion.Euler(new Vector3(0, 0, gamaAngleDeg)), Time.deltaTime * 100);
			*/
		}

		disAlphaAngleDeg = abs(alphaAngleDeg - this->preAlphaAngleDeg);
		disBetaAngleDeg = abs(betaAngleDeg - this->preBetaAngleDeg);
		disGamaAngleDeg = abs(gamaAngleDeg - this->preGamaAngleDeg);

		maxDis = max(disAlphaAngleDeg, disBetaAngleDeg);
		maxDis = max(maxDis, disGamaAngleDeg);


		this->preAlphaAngleDeg  = alphaAngleDeg; // alpha açısının radyan değeri
		this->preBetaAngleDeg = betaAngleDeg; // beta açısının radyan değeri
		this->preGamaAngleDeg = gamaAngleDeg; // gama açısının radyan değeri

		this->delayTime = ceil(maxDis * 200 / 60);

	}

};



#endif /* SRC_LEG_LEG_H_ */
