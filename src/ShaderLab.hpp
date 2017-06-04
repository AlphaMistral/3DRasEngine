//
//  ShaderLab.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/5.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef ShaderLab_hpp
#define ShaderLab_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include "RasMath.hpp"
#include "Model.hpp"
#include "ShaderProperty.hpp"

class ShaderLab
{
public:
    
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
    
    static Vertex VertexShader(const VertexInput&);
    static Vertex VertexShaderSimple(const VertexInput&);
    
    static Vector4 FragmentDepth(const Model&, const Vertex&);
    static Vector4 FragmentLambertian(const Model&, const Vertex&);
    static Vector4 FragmentBlinnPhong(const Model&, const Vertex&);
};

typedef Vector4 (*FShader) (const Model &, const Vertex &);
typedef Vertex (*VShader) (const VertexInput &);

#endif /* ShaderLab_hpp */
