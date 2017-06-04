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
    mat.Invert();
    return mat;
}

Matrix4x4 RasTransform :: CreateModelMatrix (const Vector4 &translate)
{
    Matrix4x4 mat;
    mat.m[3][0] = translate.x; mat.m[3][1] = translate.y; mat.m[3][2] = translate.z;
    return mat;
}

Matrix4x4 RasTransform :: CreateTranslationMatrix(const Vector3 &translation)
{
    Matrix4x4 mat;
    mat.m[3][0] = translation.x;
    mat.m[3][1] = translation.y;
    mat.m[3][2] = translation.z;
    return mat;
}

Matrix4x4 RasTransform :: CreateScaleMatrix(const Vector3 &scales)
{
    Matrix4x4 mat;
    mat.m[0][0] = scales.x;
    mat.m[1][1] = scales.y;
    mat.m[2][2] = scales.z;
    return mat;
}

Matrix4x4 RasTransform :: CreateScaleMatrix(const Vector3 &axis, const float k)
{
    Matrix4x4 mat;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    mat.m[0][0] = 1 + (k - 1) * x * x;
    mat.m[0][1] = (k - 1) * x * y;
    mat.m[0][2] = (k - 1) * x * z;
    mat.m[1][0] = (k - 1) * x * y;
    mat.m[1][1] = 1 + (k - 1) * y * y;
    mat.m[1][2] = (k - 1) * y * z;
    mat.m[2][0] = (k - 1) * x * z;
    mat.m[2][1] = (k - 1) * y * z;
    mat.m[2][2] = 1 + (k - 1) * z * z;
    return mat;
}

Matrix4x4 RasTransform :: CreateRotationMatrixFromEulerAngles(const Vector3 &eulerAngles)
{
    Matrix4x4 mat;
    float h = eulerAngles.y;
    float p = eulerAngles.x;
    float b = eulerAngles.z;
    mat.m[0][0] = cos(h) * cos(b) + sin(h) * sin(p) * sin(b);
    mat.m[0][1] = sin(b) * cos(p);
    mat.m[0][2] = -sin(h) * cos(b) + cos(h) * sin(p) * sin(b);
    mat.m[1][0] = -cos(h) * sin(b) + sin(h) * sin(p) * cos(b);
    mat.m[1][1] = cos(b) * cos(p);
    mat.m[1][2] = sin(b) * sin(h) + cos(h) * sin(p) * cos(b);
    mat.m[2][0] = sin(h) * cos(p);
    mat.m[2][1] = -sin(p);
    mat.m[2][2] = cos(h) * cos(p);
    return mat;
}

Matrix4x4 RasTransform :: CreateRotationMatrixFromQuaternion(const Quaternion &q)
{
    Matrix4x4 mat;
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    mat.m[0][0] = 1 - 2 * y * y - 2 * z * z;
    mat.m[0][1] = 2 * x * y - 2 * w * z;
    mat.m[0][2] = 2 * x * z + 2 * w * y;
    mat.m[1][0] = 2 * x * y + 2 * w * z;
    mat.m[1][1] = 1 - 2 * x * x - 2 * z * z;
    mat.m[1][2] = 2 * y * z - 2 * w * x;
    mat.m[2][0] = 2 * x * z - 2 * w * y;
    mat.m[2][1] = 2 * y * z + 2 * w * x;
    mat.m[2][2] = 1 - 2 * x *x - 2 * y * y;
    return mat;
}

Matrix4x4 RasTransform :: CreateRotationMatrixFromAxis(const Vector3 &axis, const float theta)
{
    Matrix4x4 mat;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float s = sin(theta);
    float c = cos(theta);
    mat.m[0][0] = x * x * (1 - c) + c;
    mat.m[0][1] = x * y * (1 - c) - z * s;
    mat.m[0][2] = x * z * (1 - c) + y * s;
    mat.m[1][0] = x * y * (1 - c) + z * s;
    mat.m[1][1] = y * y * (1 - c) * c;
    mat.m[1][2] = y * z * (1 - c) - x * s;
    mat.m[2][0] = x * z * (1 - c) - y * s;
    mat.m[2][1] = y * z * (1 - c) + x * s;
    mat.m[2][2] = z * z * (1 - c) + c;
    return mat;
}

void RasTransform :: TranslateMatrix(Matrix4x4 &m, const Vector3 &translation)
{
    Matrix4x4 mat = CreateTranslationMatrix(translation);
    m = mat * m;
}

void RasTransform :: ScaleMatrix(Matrix4x4 &m, const Vector3 &scales)
{
    Matrix4x4 mat = CreateScaleMatrix(scales);
    m = mat * m;
}

void RasTransform :: ScaleMatrix(Matrix4x4 &m, const Vector3 &axis, const float k)
{
    Matrix4x4 mat = CreateScaleMatrix(axis, k);
    m = mat * m;
}

void RasTransform :: RotateMatrixByAxis(Matrix4x4 &m, const Vector3 &axis, const float theta)
{
    Matrix4x4 mat = CreateRotationMatrixFromAxis(axis, theta);
    m = mat * m;
}

void RasTransform :: RotateMatrixByQuaternion(Matrix4x4 &m, const Quaternion &q)
{
    Matrix4x4 mat = CreateRotationMatrixFromQuaternion(q);
    m = mat * m;
}

void RasTransform :: RotateMatrixByEulerAngles(Matrix4x4 &m, const Vector3 &eulerAngles)
{
    Matrix4x4 mat = CreateRotationMatrixFromEulerAngles(eulerAngles);
    m = mat * m;
}

Matrix4x4 RasTransform :: CreateModelMatrix()
{
    Matrix4x4 mat;
    return mat;
}

Matrix4x4 RasTransform :: CreateModelMatrix(Vector3 &translation, Vector3 &scales, Vector3 &eulerAngles)
{
    return CreateScaleMatrix(scales) * CreateRotationMatrixFromEulerAngles(eulerAngles) * CreateTranslationMatrix(translation);
}

Matrix4x4 RasTransform :: CreateModelMatrix(Vector3 &translation, Vector3 &scales, Quaternion &q)
{
    return CreateScaleMatrix(scales) * CreateRotationMatrixFromQuaternion(q) * CreateTranslationMatrix(translation);
}

