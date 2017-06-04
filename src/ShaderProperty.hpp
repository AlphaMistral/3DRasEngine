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
#include "ObjectProperties.hpp"

using namespace std;

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

Vertex VV (const VertexInput &inVertex);

auto FragmentShaderDepth = [] (const Vertex &i) -> Vector4
{
    float depth = (i.pos.z - 0.1) / (1000 - 0.1) * 100;
    return Vector4(depth, depth, depth, 1.0f);
};

#endif /* ShaderProperty_hpp */
