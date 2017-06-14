//
//  Material.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/14.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include "ShaderLab.hpp"

class Material
{
public:
    const Uniform *uniform;
    VShader vertexShader;
    FShader fragmentShader;
    
    Material();
    Material(const Uniform *, const VShader, const FShader);
};

#endif /* Material_hpp */
