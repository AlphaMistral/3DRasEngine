//
//  Quaternion.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/31.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Quaternion.hpp"

void Quaternion :: identity()
{
    w = 1.0f;
    x = y = z = 0.0f;
}

void Quaternion :: setToRotateAboutX(float theta)
{
    float thetaOver2 = theta * 0.5f;
    w = cos(thetaOver2);
    x = sin(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion :: setToRotateAboutY(float theta)
{
    float thetaOver2 = theta * 0.5f;
    w = cos(thetaOver2);
    y = sin(thetaOver2);
    x = 0.0f;
    z = 0.0f;
}

void Quaternion :: setToRotateAboutZ(float theta)
{
    float thetaOver2 = theta * 0.5f;
    w = cos(thetaOver2);
    z = sin(thetaOver2);
    x = 0.0f;
    z = 0.0f;
}

void Quaternion :: setToRotateAboutAxis(const Vector3 &axis, float theta)
{
    Vector3 normalizedAxis = axis.Normalize ();
    float thetaOver2 = theta * 0.5f;
    float sinThetaOver2 = sin(thetaOver2);
    
    w = cos(thetaOver2);
    x = normalizedAxis.x * sinThetaOver2;
    y = normalizedAxis.y * sinThetaOver2;
    z = normalizedAxis.z * sinThetaOver2;
}

Quaternion Quaternion :: operator * (const Quaternion &a) const
{
    Quaternion result;
    result.w = w * a.w - x * a.x - y * a.y - z * a.z;
    result.x = w * a.x + x * a.w + z * a.y - y * a.z;
    result.y = w * a.y + y * a.w + x * a.z - z * a.x;
    result.z = w * a.z + z * a.w + y * a.x - x * a.y;
    return result;
}

Quaternion &Quaternion :: operator *= (const Quaternion &a)
{
    *this = *this * a;
    return *this;
}

void Quaternion :: Normalize()
{
    float mag = sqrtf(w * w + x * x + y * y + z * z);
    if (mag > 0.0f)
    {
        float oneOverMag = 1.0f / mag;
        w *= oneOverMag;
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }
    else
    {
        identity();
    }
}

float Quaternion :: getRotationAngle() const
{
    float ww;
    if (w <= -1.0f)
        ww = -1.0f;
    else if (w >= 1.0f)
        ww = 1.0f;
    else ww = w;
    float thetaOver2 = acos(w);
    return thetaOver2 * 2.0f;
}

Vector3 Quaternion :: getRotationAxis() const
{
    float sinThetaOver2Sq = 1.0f - w * w;
    if (sinThetaOver2Sq <= 0.0f)
        return Vector3(1.0f, 0.0f, 0.0f);
    float oneOverSinThetaOver2 = 1.0f / sqrtf(sinThetaOver2Sq);
    return Vector3(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}

float Quaternion :: Dot(const Quaternion &a, const Quaternion &b)
{
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

Quaternion Quaternion :: Slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
    if (t <= 0.0f)
        return q0;
    else if (t >= 1.0f)
        return q1;
    float cosOmega = Dot(q0, q1);
    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;
    if (cosOmega < 0.0f)
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }
    float k0, k1;
    if (cosOmega > 0.9999f)
    {
        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
        float omega = atan2(sinOmega, cosOmega);
        float oneOverSinOmega = 1.0f / sinOmega;
        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }
    Quaternion result;
    result.x = k0 * q0.x + k1 * q1x;
    result.y = k0 * q0.y + k1 * q1y;
    result.z = k0 * q0.z + k1 * q1z;
    result.w = k0 * q0.w + k1 * q1w;
    return result;
}

Quaternion Quaternion :: Conjugate(const Quaternion &q)
{
    Quaternion result;
    result.w = q.w;
    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;
    return result;
}








