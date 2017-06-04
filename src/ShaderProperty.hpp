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
#include <cmath>

#include "RasTransform.hpp"
#include "Model.hpp"
#include "ObjectProperties.hpp"

using namespace std;

static Vector4 WORLD_SPACE_LIGHT_POS;
static Vector4 WORLD_SPACE_CAMERA_POS;
static Matrix4x4 RAS_MATRIX_M;
static Matrix4x4 RAS_MATRIX_V;
static Matrix4x4 RAS_MATRIX_P;
static Matrix4x4 RAS_MATRIX_VP;
static Matrix4x4 RAS_MATRIX_MV;
static Matrix4x4 RAS_MATRIX_MVP;
static Matrix4x4 RAS_MATRIX_IT_MV;
static Vector4 WORLD_SPACE_LIGHT_COLOR;

auto VertexShader = [] (const Vector4 &pos, const Vector4 &normal, const Vector4 &uv, Vertex &outVertex)
{
    outVertex.pos = RasTransform :: TransformPoint(pos, RAS_MATRIX_MVP);
    outVertex.viewPos = RasTransform :: TransformPoint(pos, RAS_MATRIX_MV);
    outVertex.normal = RasTransform :: TransformDir(normal, RAS_MATRIX_IT_MV).Normalize ();
    outVertex.uv = uv;
};

auto VertexShaderDepth = [] (const Vector4 &pos, const Matrix4x4 &worldMat, Vertex &outVertex)
{
    
};

auto FragmentShaderLambertian = [] (const Vertex &i) -> Vector4
{
    return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
};

auto FragmentShaderBlinnPhong = [] (const Vertex &i) -> Vector4
{
    return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
};

auto FragmentShaderDepth = [] (const Vertex &i) ->Vector4
{
    return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
};


#endif /* ShaderProperty_hpp */
