/*
 * myMath.h
 *
 *  Created on: Jul 23, 2022
 *      Author: MSI
 */

#ifndef SRC_MYMATH_MYMATH_H_
#define SRC_MYMATH_MYMATH_H_

#include "math.h"

class MyVector3
{
public:
	float x, y, z;

	MyVector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	MyVector3(float _x, float _y, float _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	MyVector3 operator + (MyVector3 const &vec)
	{
		MyVector3 result = MyVector3(0, 0, 0);

		result.x = vec.x + this->x;
		result.y = vec.y + this->y;
		result.z = vec.z + this->z;

		return result;
	}

	MyVector3 operator - (MyVector3 const &vec)
	{
		MyVector3 result;

		result.x = this->x - vec.x;
		result.y = this->y - vec.y;
		result.z = this->z - vec.z;

		return result;
	}
};

class MyVector4
{
public:
	float x, y, z, w;

	MyVector4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	};

	MyVector4(float _x, float _y, float _z, float _w)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
		this->w = _w;
	};
};

class MyQuaternion
{
public:
	float x, y, z, w;

    MyQuaternion()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    };

    void EulertoQuaternion(MyVector3 vec)
    {
        float deg2rad = 0.0174532925f;

        float X = deg2rad * vec.x;
        float Y = deg2rad * vec.y;
        float Z = deg2rad * vec.z;

        float cy = (float)cos(Z * 0.5f);
        float sy = (float)sin(Z * 0.5f);
        float cp = (float)cos(X * 0.5f);
        float sp = (float)sin(X * 0.5f);
        float cr = (float)cos(Y * 0.5f);
        float sr = (float)sin(Y * 0.5f);

        this->w = cr * cp * cy + sr * sp * sy;
        this->x = cr * sp * cy + sr * cp * sy;
        this->y = sr * cp * cy - cr * sp * sy;
        this->z = cr * cp * sy - sr * sp * cy;
    };
};

class MyMatrix4x4
{
public:
	float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;

    MyMatrix4x4()
    {
        this->m00 = 0;
        this->m01 = 0;
        this->m02 = 0;
        this->m03 = 0;

        this->m10 = 0;
        this->m11 = 0;
        this->m12 = 0;
        this->m13 = 0;

        this->m20 = 0;
        this->m21 = 0;
        this->m22 = 0;
        this->m23 = 0;

        this->m30 = 0;
        this->m31 = 0;
        this->m32 = 0;
        this->m33 = 1;
    }

    void Rotate(MyQuaternion vec)
    {
        this->m00 = 1 - 2 * vec.y * vec.y - 2 * vec.z * vec.z;
        this->m01 = 2 * vec.x * vec.y - 2 * vec.z * vec.w;
        this->m02 = 2 * vec.x * vec.z + 2 * vec.y * vec.w;
        this->m03 = 0;

        this->m10 = 2 * vec.x * vec.y + 2 * vec.z * vec.w;
        this->m11 = 1 - 2 * vec.x * vec.x - 2 * vec.z * vec.z;
        this->m12 = 2 * vec.y * vec.z - 2 * vec.x * vec.w;
        this->m13 = 0;

        this->m20 = 2 * vec.x * vec.z - 2 * vec.y * vec.w;
        this->m21 = 2 * vec.y * vec.z + 2 * vec.x * vec.w;
        this->m22 = 1 - 2 * vec.x * vec.x - 2 * vec.y * vec.y;
        this->m23 = 0;
    }

    void Inverse()
    {

        float det =
            this->m03 * this->m12 * this->m21 * this->m30 - this->m02 * this->m13 * this->m21 * this->m30 - this->m03 * this->m11 * this->m22 * this->m30 + this->m01 * this->m13 * this->m22 * this->m30 +
            this->m02 * this->m11 * this->m23 * this->m30 - this->m01 * this->m12 * this->m23 * this->m30 - this->m03 * this->m12 * this->m20 * this->m31 + this->m02 * this->m13 * this->m20 * this->m31 +
            this->m03 * this->m10 * this->m22 * this->m31 - this->m00 * this->m13 * this->m22 * this->m31 - this->m02 * this->m10 * this->m23 * this->m31 + this->m00 * this->m12 * this->m23 * this->m31 +
            this->m03 * this->m11 * this->m20 * this->m32 - this->m01 * this->m13 * this->m20 * this->m32 - this->m03 * this->m10 * this->m21 * this->m32 + this->m00 * this->m13 * this->m21 * this->m32 +
            this->m01 * this->m10 * this->m23 * this->m32 - this->m00 * this->m11 * this->m23 * this->m32 - this->m02 * this->m11 * this->m20 * this->m33 + this->m01 * this->m12 * this->m20 * this->m33 +
            this->m02 * this->m10 * this->m21 * this->m33 - this->m00 * this->m12 * this->m21 * this->m33 - this->m01 * this->m10 * this->m22 * this->m33 + this->m00 * this->m11 * this->m22 * this->m33;

        det = 1 / det;

        float _m00 = det*(this->m12 * this->m23 * this->m31 - this->m13 * this->m22 * this->m31 + this->m13 * this->m21 * this->m32 - this->m11 * this->m23 * this->m32 - this->m12 * this->m21 * this->m33 + this->m11 * this->m22 * this->m33);
        float _m01 = det*(this->m03 * this->m22 * this->m31 - this->m02 * this->m23 * this->m31 - this->m03 * this->m21 * this->m32 + this->m01 * this->m23 * this->m32 + this->m02 * this->m21 * this->m33 - this->m01 * this->m22 * this->m33);
        float _m02 = det*(this->m02 * this->m13 * this->m31 - this->m03 * this->m12 * this->m31 + this->m03 * this->m11 * this->m32 - this->m01 * this->m13 * this->m32 - this->m02 * this->m11 * this->m33 + this->m01 * this->m12 * this->m33);
        float _m03 = det*(this->m03 * this->m12 * this->m21 - this->m02 * this->m13 * this->m21 - this->m03 * this->m11 * this->m22 + this->m01 * this->m13 * this->m22 + this->m02 * this->m11 * this->m23 - this->m01 * this->m12 * this->m23);
        float _m10 = det*(this->m13 * this->m22 * this->m30 - this->m12 * this->m23 * this->m30 - this->m13 * this->m20 * this->m32 + this->m10 * this->m23 * this->m32 + this->m12 * this->m20 * this->m33 - this->m10 * this->m22 * this->m33);
        float _m11 = det*(this->m02 * this->m23 * this->m30 - this->m03 * this->m22 * this->m30 + this->m03 * this->m20 * this->m32 - this->m00 * this->m23 * this->m32 - this->m02 * this->m20 * this->m33 + this->m00 * this->m22 * this->m33);
        float _m12 = det*(this->m03 * this->m12 * this->m30 - this->m02 * this->m13 * this->m30 - this->m03 * this->m10 * this->m32 + this->m00 * this->m13 * this->m32 + this->m02 * this->m10 * this->m33 - this->m00 * this->m12 * this->m33);
        float _m13 = det*(this->m02 * this->m13 * this->m20 - this->m03 * this->m12 * this->m20 + this->m03 * this->m10 * this->m22 - this->m00 * this->m13 * this->m22 - this->m02 * this->m10 * this->m23 + this->m00 * this->m12 * this->m23);
        float _m20 = det*(this->m11 * this->m23 * this->m30 - this->m13 * this->m21 * this->m30 + this->m13 * this->m20 * this->m31 - this->m10 * this->m23 * this->m31 - this->m11 * this->m20 * this->m33 + this->m10 * this->m21 * this->m33);
        float _m21 = det*(this->m03 * this->m21 * this->m30 - this->m01 * this->m23 * this->m30 - this->m03 * this->m20 * this->m31 + this->m00 * this->m23 * this->m31 + this->m01 * this->m20 * this->m33 - this->m00 * this->m21 * this->m33);
        float _m22 = det*(this->m01 * this->m13 * this->m30 - this->m03 * this->m11 * this->m30 + this->m03 * this->m10 * this->m31 - this->m00 * this->m13 * this->m31 - this->m01 * this->m10 * this->m33 + this->m00 * this->m11 * this->m33);
        float _m23 = det*(this->m03 * this->m11 * this->m20 - this->m01 * this->m13 * this->m20 - this->m03 * this->m10 * this->m21 + this->m00 * this->m13 * this->m21 + this->m01 * this->m10 * this->m23 - this->m00 * this->m11 * this->m23);
        float _m30 = det*(this->m12 * this->m21 * this->m30 - this->m11 * this->m22 * this->m30 - this->m12 * this->m20 * this->m31 + this->m10 * this->m22 * this->m31 + this->m11 * this->m20 * this->m32 - this->m10 * this->m21 * this->m32);
        float _m31 = det*(this->m01 * this->m22 * this->m30 - this->m02 * this->m21 * this->m30 + this->m02 * this->m20 * this->m31 - this->m00 * this->m22 * this->m31 - this->m01 * this->m20 * this->m32 + this->m00 * this->m21 * this->m32);
        float _m32 = det*(this->m02 * this->m11 * this->m30 - this->m01 * this->m12 * this->m30 - this->m02 * this->m10 * this->m31 + this->m00 * this->m12 * this->m31 + this->m01 * this->m10 * this->m32 - this->m00 * this->m11 * this->m32);
        float _m33 = det*(this->m01 * this->m12 * this->m20 - this->m02 * this->m11 * this->m20 + this->m02 * this->m10 * this->m21 - this->m00 * this->m12 * this->m21 - this->m01 * this->m10 * this->m22 + this->m00 * this->m11 * this->m22);

        this->m00 = _m00;
        this->m01 = _m01;
        this->m02 = _m02;
        this->m03 = _m03;
        this->m10 = _m10;
        this->m11 = _m11;
        this->m12 = _m12;
        this->m13 = _m13;
        this->m20 = _m20;
        this->m21 = _m21;
        this->m22 = _m22;
        this->m23 = _m23;
        this->m30 = _m30;
        this->m31 = _m31;
        this->m32 = _m32;
        this->m33 = _m33;
    }

    MyVector4 operator * (MyVector4 vec)
    {
        MyVector4 result = MyVector4(0, 0, 0, 0);

        result.x = this->m00 * vec.x + this->m01 * vec.y + this->m02 * vec.z + this->m03 * vec.w;
        result.y = this->m10 * vec.x + this->m11 * vec.y + this->m12 * vec.z + this->m13 * vec.w;
        result.z = this->m20 * vec.x + this->m21 * vec.y + this->m22 * vec.z + this->m23 * vec.w;
        result.w = this->m30 * vec.x + this->m31 * vec.y + this->m32 * vec.z + this->m33 * vec.w;

        return result;
    }
};

#endif /* SRC_MYMATH_MYMATH_H_ */




