//
//  Light.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/4.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "Vector.hpp"
#include "Matrix.hpp"

using namespace std;

enum LightType
{
    Directional,
    Point,
    Spot
};

class Light
{
public:
    LightType type;
    Matrix4x4 worldMat;
    Vector4 color;
    float intensity;
    Light ();
    Light (LightType type, Matrix4x4 worldMat, Vector4 c = Vector4(0.87f, 0.87f, 0.87f, 1.0f), float i = 1.0f);
    virtual void GenerateShadowMap ();
    
};

class DirectionalLight : public Light
{
public:
    virtual void GenerateShadowMap (); //ortho
};

class PointLight : public Light
{
public:
    virtual void GenerateShadowMap (); //cubeMap
};

class SpotLight : public Light
{
public:
    float angle; // [0, pi];
    virtual void GenerateShadowMap (); //Pers
};

#endif /* Light_hpp */
