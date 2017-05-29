//
//  RasTransform.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef RasTransform_hpp
#define RasTransform_hpp

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include "Vector.hpp"
#include "Matrix.hpp"

class RasTransform
{
public:
    static Vector4 TransformPoint (const Vector4 &b, const Matrix4x4 mat);
    static Vector4 TransformDir (const Vector4 &b, const Matrix4x4 mat);
    static Matrix4x4 CreateProjectionMatrix (float fov, float aspr, float np, float fp);
    static Matrix4x4 CreateViewMatrix (const Vector4 &look, const Vector4 &at, const Vector4 &up);
    static Matrix4x4 CreateModelMatrix (const Vector4 &translate);
};

#endif /* RasTransform_hpp */
