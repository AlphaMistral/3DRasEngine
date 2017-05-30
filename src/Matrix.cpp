//
//  Matrix.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Matrix.hpp"

Matrix4x4 :: Matrix4x4 ()
{
    memset(m, 0, sizeof (m));
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

Matrix4x4 Matrix4x4 :: operator * (const Matrix4x4 &rhs) const
{
    Matrix4x4 temp;
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            temp.m[i][j] = m[i][0] * rhs.m[0][j] + m[i][1] * rhs.m[1][j] + m[i][2] * rhs.m[2][j] + m[i][3] * rhs.m[3][j];
        }
    }
    return temp;
}

Matrix4x4 Matrix4x4 :: operator * (const float x) const
{
    Matrix4x4 temp;
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            temp.m[i][j] = m[i][j] * x;
        }
    }
    return temp;
}

void Matrix4x4 :: Invert ()
{
    Matrix4x4 temm = *this;
    float tmp[12];
    tmp[0] = temm.m[2][2] * temm.m[3][3];
    tmp[1] = temm.m[3][2] * temm.m[2][3];
    tmp[2] = temm.m[1][2] * temm.m[3][3];
    tmp[3] = temm.m[3][2] * temm.m[1][3];
    tmp[4] = temm.m[1][2] * temm.m[2][3];
    tmp[5] = temm.m[2][2] * temm.m[1][3];
    tmp[6] = temm.m[0][2] * temm.m[3][3];
    tmp[7] = temm.m[3][2] * temm.m[0][3];
    tmp[8] = temm.m[0][2] * temm.m[2][3];
    tmp[9] = temm.m[2][2] * temm.m[0][3];
    tmp[10] = temm.m[0][2] * temm.m[1][3];
    tmp[11] = temm.m[1][2] * temm.m[0][3];
    m[0][0] = tmp[0] * temm.m[1][1] + tmp[3] * temm.m[2][1] + tmp[4] * temm.m[3][1];
    m[0][0] -= tmp[1] * temm.m[1][1] + tmp[2] * temm.m[2][1] + tmp[5] * temm.m[3][1];
    m[0][1] = tmp[1] * temm.m[0][1] + tmp[6] * temm.m[2][1] + tmp[9] * temm.m[3][1];
    m[0][1] -= tmp[0] * temm.m[0][1] + tmp[7] * temm.m[2][1] + tmp[8] * temm.m[3][1];
    m[0][2] = tmp[2] * temm.m[0][1] + tmp[7] * temm.m[1][1] + tmp[10] * temm.m[3][1];
    m[0][2] -= tmp[3] * temm.m[0][1] + tmp[6] * temm.m[1][1] + tmp[11] * temm.m[3][1];
    m[0][3] = tmp[5] * temm.m[0][1] + tmp[8] * temm.m[1][1] + tmp[11] * temm.m[2][1];
    m[0][3] -= tmp[4] * temm.m[0][1] + tmp[9] * temm.m[1][1] + tmp[10] * temm.m[2][1];
    m[1][0] = tmp[1] * temm.m[1][0] + tmp[2] * temm.m[2][0] + tmp[5] * temm.m[3][0];
    m[1][0] -= tmp[0] * temm.m[1][0] + tmp[3] * temm.m[2][0] + tmp[4] * temm.m[3][0];
    m[1][1] = tmp[0] * temm.m[0][0] + tmp[7] * temm.m[2][0] + tmp[8] * temm.m[3][0];
    m[1][1] -= tmp[1] * temm.m[0][0] + tmp[6] * temm.m[2][0] + tmp[9] * temm.m[3][0];
    m[1][2] = tmp[3] * temm.m[0][0] + tmp[6] * temm.m[1][0] + tmp[11] * temm.m[3][0];
    m[1][2] -= tmp[2] * temm.m[0][0] + tmp[7] * temm.m[1][0] + tmp[10] * temm.m[3][0];
    m[1][3] = tmp[4] * temm.m[0][0] + tmp[9] * temm.m[1][0] + tmp[10] * temm.m[2][0];
    m[1][3] -= tmp[5] * temm.m[0][0] + tmp[8] * temm.m[1][0] + tmp[11] * temm.m[2][0];
    tmp[0] = temm.m[2][0] * temm.m[3][1];
    tmp[1] = temm.m[3][0] * temm.m[2][1];
    tmp[2] = temm.m[1][0] * temm.m[3][1];
    tmp[3] = temm.m[3][0] * temm.m[1][1];
    tmp[4] = temm.m[1][0] * temm.m[2][1];
    tmp[5] = temm.m[2][0] * temm.m[1][1];
    tmp[6] = temm.m[0][0] * temm.m[3][1];
    tmp[7] = temm.m[3][0] * temm.m[0][1];
    tmp[8] = temm.m[0][0] * temm.m[2][1];
    tmp[9] = temm.m[2][0] * temm.m[0][1];
    tmp[10] = temm.m[0][0] * temm.m[1][1];
    tmp[11] = temm.m[1][0] * temm.m[0][1];
    m[2][0] = tmp[0] * temm.m[1][3] + tmp[3] * temm.m[2][3] + tmp[4] * temm.m[3][3];
    m[2][0] -= tmp[1] * temm.m[1][3] + tmp[2] * temm.m[2][3] + tmp[5] * temm.m[3][3];
    m[2][1] = tmp[1] * temm.m[0][3] + tmp[6] * temm.m[2][3] + tmp[9] * temm.m[3][3];
    m[2][1] -= tmp[0] * temm.m[0][3] + tmp[7] * temm.m[2][3] + tmp[8] * temm.m[3][3];
    m[2][2] = tmp[2] * temm.m[0][3] + tmp[7] * temm.m[1][3] + tmp[10] * temm.m[3][3];
    m[2][2] -= tmp[3] * temm.m[0][3] + tmp[6] * temm.m[1][3] + tmp[11] * temm.m[3][3];
    m[2][3] = tmp[5] * temm.m[0][3] + tmp[8] * temm.m[1][3] + tmp[11] * temm.m[2][3];
    m[2][3] -= tmp[4] * temm.m[0][3] + tmp[9] * temm.m[1][3] + tmp[10] * temm.m[2][3];
    m[3][0] = tmp[2] * temm.m[2][2] + tmp[5] * temm.m[3][2] + tmp[1] * temm.m[1][2];
    m[3][0] -= tmp[4] * temm.m[3][2] + tmp[0] * temm.m[1][2] + tmp[3] * temm.m[2][2];
    m[3][1] = tmp[8] * temm.m[3][2] + tmp[0] * temm.m[0][2] + tmp[7] * temm.m[2][2];
    m[3][1] -= tmp[6] * temm.m[2][2] + tmp[9] * temm.m[3][2] + tmp[1] * temm.m[0][2];
    m[3][2] = tmp[6] * temm.m[1][2] + tmp[11] * temm.m[3][2] + tmp[3] * temm.m[0][2];
    m[3][2] -= tmp[10] * temm.m[3][2] + tmp[2] * temm.m[0][2] + tmp[7] * temm.m[1][2];
    m[3][3] = tmp[10] * temm.m[2][2] + tmp[4] * temm.m[0][2] + tmp[9] * temm.m[1][2];
    m[3][3] -= tmp[8] * temm.m[1][2] + tmp[11] * temm.m[2][2] + tmp[5] * temm.m[0][2];
    float idet = 1.0f / (temm.m[0][0] * m[0][0] + temm.m[1][0] * m[0][1] + temm.m[2][0] * m[0][2] + temm.m[3][0] * m[0][3]);
    m[0][0] *= idet; m[0][1] *= idet; m[0][2] *= idet; m[0][3] *= idet;
    m[1][0] *= idet; m[1][1] *= idet; m[1][2] *= idet; m[1][3] *= idet;
    m[2][0] *= idet; m[2][1] *= idet; m[2][2] *= idet; m[2][3] *= idet;
    m[3][0] *= idet; m[3][1] *= idet; m[3][2] *= idet; m[3][3] *= idet;
}

Matrix4x4 Matrix4x4 :: InvertTranspose () const
{
    Matrix4x4 temp, o = *this;
    o.Invert ();
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
            temp.m[i][j] = o.m[j][i];
    return temp;
}
