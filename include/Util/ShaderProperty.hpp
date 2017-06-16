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

enum CullingOption
{
    Back,
    Front,
    Off
};

class Uniform
{
public:
    CullingOption culling;
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
        culling = CullingOption :: Back;
        ka = a;
        kd = d;
        ks = s;
        BMPManager :: LoadBMP(texture, fileName);
    }
};

class UniformTransparentShield : public Uniform
{
public:
	Vector4 color;
	UniformTransparentShield (const Vector4 &c)
	{
        culling = CullingOption :: Back;
		color = c;
	}
};

class UniformOutline : public Uniform
{
public:
    Vector4 outlineColor;
    UniformOutline (const Vector4 &c)
    {
        culling = CullingOption :: Back;
        outlineColor = c;
    }
};

class UniformToon : public Uniform
{
public:
    float shininess;
    Vector4 diffuseSegment;
    float specularSegment;
    UniformToon (const float s, const float ss, const Vector4 &d)
    {
        shininess = s;
        specularSegment = ss;
        diffuseSegment = d;
    }
};

#endif /* ShaderProperty_hpp */
