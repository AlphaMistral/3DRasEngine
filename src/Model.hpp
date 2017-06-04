//
//  Model.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>

#include "RasTransform.hpp"
#include "Mesh.hpp"
#include "BMPManager.hpp"

using namespace std;

class Model : public Mesh
{
public:
    Material material;
    Matrix4x4 worldMat;
    Model (string name, const Vector4 &pos, Material m);
    void LoadOBJ (string name);
};

#endif /* Model_hpp */
