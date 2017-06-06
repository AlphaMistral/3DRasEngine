//
//  RenderObject.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/6.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "Model.hpp"
#include "ShaderProperty.hpp"

///Please do not ask me why I name the "Material" as "Uniform".
///2 b honest, I was drunk when coding that part.
///I mean, literally drunk. 1750g of ErGuoTou. Yeah according 2 my friend, 1750g.
class RenderObject
{
public:
    Model model;
    Uniform *material;
    RenderObject (const Model &, Uniform *);
};

#endif /* RenderObject_hpp */
