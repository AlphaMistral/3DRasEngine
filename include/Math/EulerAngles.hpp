//
//  EulerAngles.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/1.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef EulerAngles_hpp
#define EulerAngles_hpp

#include <cstdio>
#include <cmath>

#include "Quaternion.hpp"
#include "Matrix.hpp"

struct RotationMatrix;

struct EulerAngles
{
    float heading, pitch, bank;
    EulerAngles();
    EulerAngles(float h, float p, float b);
    
    void identity ();
    void canoize ();
    void fromObjectToInertialQuaternion(const Quaternion &q);
    void fromInertialToObjectQuaternion(const Quaternion &q);
    
    void fromObjectToWorldMatrix(const Matrix4x4 &m);
    void fromWorldToObjectMatrix(const Matrix4x4 &m);
    
    void fromRotationMatrix(const RotationMatrix &m);
};

#endif /* EulerAngles_hpp */
