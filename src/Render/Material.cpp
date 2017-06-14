//
//  Material.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/14.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Material.hpp"

Material :: Material()
{
    vertexShader = NULL;
    fragmentShader = NULL;
    uniform = NULL;
}

Material :: Material (const Uniform *uni, const VShader v, const FShader f)
{
    uniform = uni;
    vertexShader = v;
    fragmentShader = f;
}
