//
//  ShaderProperty.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/5.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "ShaderProperty.hpp"

Vertex VV (const VertexInput &inVertex)
{
    Vertex outVertex;
    outVertex.pos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MVP);
    outVertex.viewPos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MV);
    outVertex.normal = RasTransform :: TransformDir(inVertex.normal, RAS_MATRIX_IT_MV).Normalize ();
    outVertex.uv = inVertex.uv;
    return outVertex;
};
