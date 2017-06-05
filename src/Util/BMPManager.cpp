//
//  BMPManager.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "BMPManager.hpp"

void BMPManager :: SaveBMP (std::vector<Vector4> &frameBuffer, int width, int height, std::string fileName)
{
#define INT2CHAR_BIT(num, bit) (unsigned char)(((num) >> (bit)) & 0xff)
#define INT2CHAR(num) INT2CHAR_BIT((num),0), INT2CHAR_BIT((num),8), INT2CHAR_BIT((num),16), INT2CHAR_BIT((num),24)
    unsigned char buf[54] = { 'B', 'M', INT2CHAR (54 + width*height * 32), INT2CHAR (0), INT2CHAR (54), INT2CHAR (40), INT2CHAR (width), INT2CHAR (height), 1, 0, 32, 0 };
    std::ofstream ofs (fileName, std::ios_base::out | std::ios_base::binary);
    ofs.write ((char *)buf, sizeof (buf));
    for (auto &color : frameBuffer)
	{
        buf[0] = (unsigned char)std::min (255, (int)(color.z * 255));
        buf[1] = (unsigned char)std::min (255, (int)(color.y * 255));
        buf[2] = (unsigned char)std::min (255, (int)(color.x * 255));
        buf[3] = (unsigned char)std::min (255, (int)(color.w * 255));
        ofs.write ((char *)buf, 4);
    }
}

bool BMPManager :: LoadBMP (Texture &texture, std::string fileName)
{
    std::ifstream is (fileName, std::ios_base::binary);
    if (!is) return false;
    unsigned char buf[54];
    is.read ((char *)buf, sizeof (buf));
    // in bmp header, height could be negtive
    texture.width = *(int *)&buf[18], texture.height = abs (*(int *)&buf[22]);
    // smax/tmax is use for texture filtering
    texture.smax = texture.width - 1.5f, texture.tmax = texture.height - 1.5f;
    int bytes = buf[28] / 8, count = texture.width * texture.height * bytes;
    unsigned char *tmp = new unsigned char[count];
    is.read ((char *)tmp, count);
    texture.data.resize (texture.width * texture.height);
    count = 0;
    for (auto &color : texture.data)
	{
        color = { tmp[count + 2] / 255.0f, tmp[count + 1] / 255.0f, tmp[count + 0] / 255.0f, 0.0f };
        count += bytes;
    }
    delete[]tmp;
    return true;
}

