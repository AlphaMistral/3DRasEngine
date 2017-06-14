//
//  Matrix.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>

struct Matrix4x4
{
    float m[4][4];
    Matrix4x4 ();
	Matrix4x4 (const Matrix4x4 &);
    Matrix4x4 operator * (const Matrix4x4 &rhs) const;
    Matrix4x4 operator * (const float x) const;
    void Invert ();
    Matrix4x4 InvertTranspose () const;
};

#endif /* Matrix_hpp */
