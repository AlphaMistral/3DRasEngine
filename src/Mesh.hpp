//
//  Mesh.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "RasMath.hpp"
#include "ObjectProperties.hpp"

using namespace std;

class Mesh
{
public:
    Mesh (){}
    
    vector <Vector4> vertex, normal, uv;
    vector <Index> index;
};

#endif /* Mesh_hpp */
