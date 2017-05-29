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
