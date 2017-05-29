//
//  Model.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Model.hpp"

Model :: Model (string name, const Vector4 &pos, Material m)
{
    material = m;
    vertex = vector<Vector4> (1, {0});
    normal = vector<Vector4> (1, {0});
    uv = vector <Vector4> (1, {0});
    worldMat = RasTransform::CreateModelMatrix(pos);
    LoadOBJ(name + ".obj");
    if (uv.size() > 1)
        BMPManager::LoadBMP(material.texture, name + ".bmp");
}

void Model :: LoadOBJ(string str)
{
    float x, y, z;
    char dummy;
    ifstream iss (str);
    while (getline (iss, str))
    {
        if (str.length() < 2)continue;
        istringstream istr (str);
        string token;
        if (str[1] == 't' && str[0] == 'v')
        {
            istr >> token >> x >> y;
            uv.push_back({x, y});
        }
        else if (str[1] == 'n' && str[0] == 'v')
        {
            istr >> token >> x >> y >> z;
            normal.push_back({x, y, z});
        }
        else if (str[0] == 'v')
        {
            istr >> token >> x >> y >> z;
            vertex.push_back({x, y, z});
        }
        else if (str[0] == 'f')
        {
            Index idx = {{0}};
            if (str.find("//") != string::npos)
            {
                istr >> token >> idx.pos[0] >> dummy >> dummy >> idx.normal[0] >> idx.pos[1] >> dummy >> dummy >> idx.normal[1] >> idx.pos[2] >> dummy >> dummy >> idx.normal[2];
            }
            else
            {
                size_t cnt = 0, pos = str.find('/');
                while (pos != string::npos)
                {
                    cnt++;
                    pos= str.find('/', pos + 1);
                }
                if (cnt == 6)
                {
                    istr >> token >> idx.pos[0] >> dummy >> idx.uv[0] >> dummy >> idx.normal[0] >> idx.pos[1] >> dummy >> idx.uv[1] >> dummy >> idx.normal[1] >> idx.pos[2] >> dummy >> idx.uv[2] >> dummy >> idx.normal[2];

                }
                else if (cnt == 3)
                {
                    istr >> token >> idx.pos[0] >> dummy >> idx.uv[0] >> idx.pos[1] >> dummy >> idx.uv[1] >> idx.pos[2] >> dummy >> idx.uv[2];
                }
            }
            index.push_back(idx);
        }
    }
    for (auto &idx : index)
    {
        for (int i = 0;i < 3;i++)
        {
            if (idx.pos[i] < 0)idx.pos[i] += (int)vertex.size();
            if (idx.uv[i] < 0)idx.uv[i] += (int)uv.size();
            if (idx.normal[i] < 0)idx.normal[i] += (int)normal.size();
        }
    }
}
