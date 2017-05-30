//
//  RasTransform.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "RasTransform.hpp"

Vector4 RasTransform :: TransformPoint (const Vector4 &b, const Matrix4x4 mat)
{
    Vector4 v;
    v.w = b.x * mat.m[0][3] + b.y * mat.m[1][3] + b.z * mat.m[2][3] + mat.m[3][3];
    v.x = (b.x * mat.m[0][0] + b.y * mat.m[1][0] + b.z * mat.m[2][0] + mat.m[3][0]) / v.w;
    v.y = (b.x * mat.m[0][1] + b.y * mat.m[1][1] + b.z * mat.m[2][1] + mat.m[3][1]) / v.w;
    v.z = (b.x * mat.m[0][2] + b.y * mat.m[1][2] + b.z * mat.m[2][2] + mat.m[3][2]) / v.w;
    return v;
}

Vector4 RasTransform :: TransformDir (const Vector4 &b, const Matrix4x4 mat)
{
    Vector4 v;
    v.w = 0.0f;
    v.x = b.x * mat.m[0][0] + b.y * mat.m[1][0] + b.z * mat.m[2][0];
    v.y = b.x * mat.m[0][1] + b.y * mat.m[1][1] + b.z * mat.m[2][1];
    v.z = b.x * mat.m[0][2] + b.y * mat.m[1][2] + b.z * mat.m[2][2];
    return v;
}

Matrix4x4 RasTransform :: CreateProjectionMatrix (float fov, float aspr, float np, float fp)
{
    float rBound = np * tan (fov * 0.5f);
    float lBound = -rBound;
    float bBound = lBound / aspr;
    float tBound = rBound / aspr;
    Matrix4x4 mat;
    mat.m[0][0] = 2 * np / (rBound - lBound);
    mat.m[1][1] = 2 * np / (tBound - bBound);
    mat.m[2][0] = (rBound + lBound) / (rBound - lBound);
    mat.m[2][1] = (tBound + bBound) / (tBound - bBound);
    mat.m[2][2] = -(fp + np) / (fp - np);
    mat.m[2][3] = -1.0f;
    mat.m[3][2] = (-2.0f * fp * np) / (fp - np);
    mat.m[0][1] = mat.m[0][2] = mat.m[0][3] = 0.0f;
    mat.m[1][0] = mat.m[1][2] = mat.m[1][3] = 0.0f;
    mat.m[3][0] = mat.m[3][1] = mat.m[3][3] = 0.0f;
    return mat;
}

Matrix4x4 RasTransform :: CreateViewMatrix (const Vector4 &look, const Vector4 &at, const Vector4 &up)
{
    Vector4 zAxis = (look - at).Normalize (), xAxis = up.Cross (zAxis).Normalize (), yAxis = zAxis.Cross (xAxis);
    Matrix4x4 mat;
    mat.m[0][0] = xAxis.x; mat.m[0][1] = xAxis.y; mat.m[0][2] = xAxis.z; mat.m[0][3] = 0.0f;
    mat.m[1][0] = yAxis.x; mat.m[1][1] = yAxis.y; mat.m[1][2] = yAxis.z; mat.m[1][3] = 0.0f;
    mat.m[2][0] = zAxis.x; mat.m[2][1] = zAxis.y; mat.m[2][2] = zAxis.z; mat.m[2][3] = 0.0f;
    mat.m[3][0] = look.x; mat.m[3][1] = look.y; mat.m[3][2] = look.z; mat.m[3][3] = 1.0f;
    mat.Invert ();
    return mat;
}

Matrix4x4 RasTransform :: CreateModelMatrix (const Vector4 &translate)
{
    Matrix4x4 mat;
    mat.m[3][0] = translate.x; mat.m[3][1] = translate.y; mat.m[3][2] = translate.z;
    return mat;
}

Matrix4x4 RasTransform :: RotateMatrixByEuler (Matrix4x4 m, float h, float p, float b)
{
    Matrix4x4 mat;
    mat.m[0][0] = cos(h) * cos(b) + sin(h) * sin(p) * sin(b);
    mat.m[0][1] = sin(b) * cos(p);
    mat.m[0][2] = -sin(h) * cos(b) + cos(h) * sin(p) * sin(b);
    mat.m[1][0] = -cos(h) * sin(b) + sin(h) * sin(p) * cos(b);
    mat.m[1][1] = cos(b) * cos(p);
    mat.m[1][2] = sin(b) * sin(h) + cos(h) * sin(p) * cos(b);
    mat.m[2][0] = sin(h) * cos(p);
    mat.m[2][1] = -sin(p);
    mat.m[2][2] = cos(h) * cos(p);
    return mat * m;
}

Matrix4x4 RasTransform :: ScaleMatrix (const Matrix4x4 m, const float x, const float y, const float z)
{
    Matrix4x4 mat;
    mat.m[0][0] = x;
    mat.m[1][1] = y;
    mat.m[2][2] = z;
    return mat * m;
}

