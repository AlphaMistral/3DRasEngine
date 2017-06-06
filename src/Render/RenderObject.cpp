//
//  RenderObject.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/6.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "RenderObject.hpp"

RenderObject :: RenderObject (const Model &mod, Uniform *uni)
{
    model = mod;
    material = uni;
}
