//
//  ShaderLab.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/5.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "ShaderLab.hpp"

Vector4 ShaderLab :: WORLD_SPACE_LIGHT_POS;
Vector4 ShaderLab :: WORLD_SPACE_CAMERA_POS;
Matrix4x4 ShaderLab :: RAS_MATRIX_M;
Matrix4x4 ShaderLab :: RAS_MATRIX_V;
Matrix4x4 ShaderLab :: RAS_MATRIX_P;
Matrix4x4 ShaderLab :: RAS_MATRIX_VP;
Matrix4x4 ShaderLab :: RAS_MATRIX_MV;
Matrix4x4 ShaderLab :: RAS_MATRIX_MVP;
Matrix4x4 ShaderLab :: RAS_MATRIX_IT_MV;
Vector4 ShaderLab :: WORLD_SPACE_LIGHT_COLOR;

static Vector4 PROJECTION_PARAMS;

Vertex ShaderLab :: VertexShader(const VertexInput &inVertex)
{
    Vertex outVertex;
    outVertex.pos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MVP);
    outVertex.viewPos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MV);
    outVertex.normal = RasTransform :: TransformDir(inVertex.normal, RAS_MATRIX_IT_MV).Normalize ();
    outVertex.uv = inVertex.uv;
    return outVertex;
}

Vector4 ShaderLab :: FragmentDepth(const Model &model, const Vertex &i)
{
    float depth = (i.pos.z - 0.1) / (1000 - 0.1) * 100;
    return Vector4(depth, depth, depth, 1.0f);
}
