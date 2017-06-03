//
//  EulerAngles.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/1.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "EulerAngles.hpp"
#include "RotationMatrix.hpp"

EulerAngles :: EulerAngles()
{
    
}

EulerAngles :: EulerAngles(float h, float p, float b)
{
    heading = h;
    pitch = p;
    bank = b;
}

void EulerAngles :: canoize()
{
    const float _Pi = acos(-1);
    const float _2Pi = 2.0f * _Pi;
    const float _PiOver2 = _Pi / 2.0f;
    const float _1OverPi = 1.0f / _Pi;
    const float _1Over2Pi = 1.0f / _2Pi;
    pitch = pitch + _Pi - floor((pitch + _Pi) * _1Over2Pi) * _2Pi - _Pi;
    if (pitch < -_PiOver2)
    {
        pitch = -_Pi - pitch;
        heading += _Pi;
        bank += _Pi;
    }
    else if (pitch > _PiOver2)
    {
        pitch = _Pi - pitch;
        heading += _Pi;
        bank += _Pi;
    }
    if(fabs(pitch) > -_PiOver2 - 1e-4)
    {
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        bank = bank + _Pi - floor((bank + _Pi) * _1Over2Pi) * _2Pi - _Pi;
    }
    heading = heading + _Pi - floor((heading + _Pi) * _1Over2Pi) * _2Pi - _Pi;
}
