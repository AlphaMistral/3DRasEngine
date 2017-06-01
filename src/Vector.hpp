//
//  Vector.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <cstdio>
#include <cmath>

struct Vector2
{
    float x, y;
    Vector2 () {}
    Vector2 (float xx, float yy = 0);
    Vector2 operator - () const;
    Vector2 operator + (const Vector2 &rhs) const;
    Vector2 operator - (const Vector2 &rhs) const;
    Vector2 operator * (const Vector2 &rhs) const;
    Vector2 operator * (float f) const;
    float Dot (const Vector2 &rhs) const;
    Vector2 Normalize () const;
};

struct Vector3
{
    float x, y, z;
    Vector3 () {}
    Vector3 (float xx, float yy = 0, float zz = 0);
    Vector3 operator - () const;
    Vector3 operator + (const Vector3 &rhs) const;
    Vector3 operator - (const Vector3 &rhs) const;
    Vector3 operator * (const Vector3 &rhs) const;
    Vector3 operator * (float f) const;
    Vector3 Cross (const Vector3 &rhs) const;
    float Dot (const Vector3 &rhs) const;
    Vector3 Normalize () const;
};

struct Vector4
{
	float x, y, z, w;
	Vector4 () {}
	Vector4 (float xx, float yy = 0, float zz = 0, float ww = 0);
	Vector4 operator - () const;
	Vector4 operator + (const Vector4 &rhs) const;
	Vector4 operator - (const Vector4 &rhs) const;
	Vector4 operator * (const Vector4 &rhs) const;
	Vector4 operator * (float f) const;
	Vector4 Cross (const Vector4 &rhs) const;
	float Dot (const Vector4 &rhs) const;
	Vector4 Normalize () const;
};

#endif /* Vector_hpp */
