//
//  Quaternion.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/31.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Quaternion.hpp"

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
