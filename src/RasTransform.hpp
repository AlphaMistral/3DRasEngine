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

#include "RasMath.hpp"

class RasTransform
{
public:
    static Vector4 TransformPoint (const Vector4 &b, const Matrix4x4 mat);
    static Vector4 TransformDir (const Vector4 &b, const Matrix4x4 mat);
    static Matrix4x4 CreateProjectionMatrix (float fov, float aspr, float np, float fp);
    static Matrix4x4 CreateViewMatrix (const Vector4 &look, const Vector4 &at, const Vector4 &up);
    static Matrix4x4 CreateModelMatrix ();
    static Matrix4x4 CreateModelMatrix (Vector3 &translation, Vector3 &scales, Vector3 &eulerAngles);
    static Matrix4x4 CreateModelMatrix (Vector3 &translation, Vector3 &scales, Quaternion &q);
    static Matrix4x4 CreateModelMatrix (const Vector4 &translate);
    
    static Matrix4x4 CreateTranslationMatrix (const Vector3 &translation);
    static Matrix4x4 CreateScaleMatrix (const Vector3 &scales);
    static Matrix4x4 CreateScaleMatrix (const Vector3 &axis, const float k);
    static Matrix4x4 CreateRotationMatrixFromAxis (const Vector3 &axis, const float theta);
    static Matrix4x4 CreateRotationMatrixFromEulerAngles (const Vector3 &eulerAngles);
    static Matrix4x4 CreateRotationMatrixFromQuaternion (const Quaternion &q);
    
    static void TranslateMatrix (Matrix4x4 &m, const Vector3 &translation);
    static void ScaleMatrix (Matrix4x4 &m, const Vector3 &scales);
    static void ScaleMatrix (Matrix4x4 &m, const Vector3 &axis, const float k);
    static void RotateMatrixByAxis (Matrix4x4 &m, const Vector3 &axis, const float theta);
    static void RotateMatrixByEulerAngles (Matrix4x4 &m, const Vector3 &eulerAngles);
    static void RotateMatrixByQuaternion (Matrix4x4 &m, const Quaternion &q);
};

#endif /* RasTransform_hpp */
