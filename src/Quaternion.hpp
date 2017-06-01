//
//  Quaternion.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/31.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <assert.h>

#include "Vector.hpp"

using namespace std;

class Quaternion
{
public:
    
    float x, y, z, w;
    
    void identity ();
    void setToRotateAboutX (float theta);
    void setToRotateAboutY (float theta);
    void setToRotateAboutZ (float theta);
    void setToRotateAboutAxis (const Vector3 &axis, float theta);
    
    Quaternion operator * (const Quaternion &a) const;
    Quaternion & operator *= (const Quaternion &a);
    
    void Normalize ();
    
    float getRotationAngle () const;
    Vector3 getRotationAxis () const;
    
    static float Dot (const Quaternion &a, const Quaternion &b);
    static Quaternion Slerp (const Quaternion &p, const Quaternion &q, float t);
    static Quaternion Conjugate (const Quaternion &q);
    static Quaternion Pow (const Quaternion &q, float exponent);
};


#endif /* Quaternion_hpp */
