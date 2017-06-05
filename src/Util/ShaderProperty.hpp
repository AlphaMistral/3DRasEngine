//
//  ShaderProperty.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/4.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef ShaderProperty_hpp
#define ShaderProperty_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <cmath>

#include "RasTransform.hpp"
#include "BMPManager.hpp"
#include "ObjectProperties.hpp"

struct VertexInput
{
    Vector4 pos;
    Vector4 normal;
    Vector4 uv;
    VertexInput () {}
    VertexInput (Vector4 p, Vector4 n, Vector4 u)
    {
        pos = p;
        normal = n;
        uv = u;
    }
};

class Uniform
{
public:
    virtual ~Uniform () {}
};

class UniformBlinnPhong : public Uniform
{
public:
    float ka;
    float kd;
    float ks;
    Texture texture;
    UniformBlinnPhong (float a, float d, float s, std::string fileName)
    {
        ka = a;
        kd = d;
        ks = s;
        BMPManager :: LoadBMP(texture, fileName);
    }
};

#endif /* ShaderProperty_hpp */
