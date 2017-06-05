//
//  BMPManager.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef BMPManager_hpp
#define BMPManager_hpp

#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Vector.hpp"
#include "ObjectProperties.hpp"

class BMPManager
{
public:
    static void SaveBMP (std::vector <Vector4> &frameBuffer, int width, int height, std::string fileName);
    static bool LoadBMP (Texture &texture, std::string fileName);
};

#endif /* BMPManager_hpp */
