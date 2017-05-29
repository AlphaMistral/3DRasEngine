//
//  ObjectProperties.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef ObjectProperties_hpp
#define ObjectProperties_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "Vector.hpp"

using namespace std;

struct Vertex { Vector4 pos, uv, normal, viewPos, color; };
struct Index { int pos[3], uv[3], normal[3]; };
struct Texture { int width, height; float smax, tmax; vector<Vector4> data; };
struct Material { float ka, kd, ks; Texture texture; };
struct Light { Vector4 pos, viewPos, ambientColor, diffuseColor, specularColor; };

#endif /* ObjectProperties_hpp */
