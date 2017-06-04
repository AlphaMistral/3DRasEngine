//
//  Light.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/4.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Light.hpp"

Light :: Light()
{
    type = LightType :: Directional;
}

Light :: Light(LightType t, Matrix4x4 mat, Vector4 c, float i)
{
    type = t;
    worldMat = mat;
    color = c;
    intensity = i;
}

void Light :: GenerateShadowMap()
{
    
}
