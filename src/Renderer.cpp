//
//  Renderer.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "Renderer.hpp"

Renderer :: Renderer (int w, int h)
{
    width = w;
    height = h;
    frameBuffer = std::vector<Vector4> (w * h, {1.0f / 256 * 195, 1.0f / 256 * 240, 1.0f / 256 * 240, 0});
    depthBuffer = std::vector<float> (w * h, std::numeric_limits<float> :: max ());
}

void Renderer :: SetFrustum (float fov, float aspr, float np, float fp)
{
    proj = RasTransform :: CreateProjectionMatrix (fov, aspr, np, fp);
}

void Renderer :: SetCamera (const Vector4 &look, const Vector4 &at)
{
    view = RasTransform :: CreateViewMatrix(look, at, {0.0f, 1.0f, 0.0f});
}

void Renderer :: SetLight (const Vector4 &pos, const Vector4 &ambi, const Vector4 &diff, const Vector4 &spec)
{
    light.pos = pos;
    light.ambientColor = ambi;
    light.diffuseColor = diff;
    light.specularColor = spec;
	
	ShaderLab :: WORLD_SPACE_LIGHT_POS = light.pos;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_AMB = light.ambientColor;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_DIF = light.diffuseColor;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_SPE = light.specularColor;
}

void Renderer :: DrawModel(Model &model, VShader vShader, FShader fShader)
{
    ShaderLab :: RAS_MATRIX_V = view;
	ShaderLab :: RAS_MATRIX_P = proj;
	ShaderLab :: RAS_MATRIX_MV = model.worldMat * view;
	ShaderLab :: RAS_MATRIX_MVP = ShaderLab :: RAS_MATRIX_MV * proj;
	ShaderLab :: RAS_MATRIX_IT_MV = ShaderLab :: RAS_MATRIX_MV.InvertTranspose();
    for (auto &idx : model.index)
    {
        Vertex outVertex[3];
        bool badTriangle = false;
        for (int i = 0;i < 3;i++)
        {
			outVertex[i] = vShader (VertexInput(model.vertex[idx.pos[i]], model.normal[idx.normal[i]], model.uv[idx.uv[i]]));
            if (outVertex[i].pos.z < 0.0f || outVertex[i].pos.z > 1.0f)
            {
                badTriangle = true;
                break;
            }
            NDC2Screen (outVertex[i].pos);
        }
        if (badTriangle || BackFaceCulling(outVertex[0].viewPos, outVertex[1].viewPos, outVertex[2].viewPos))continue;
        FillTriangle(model, outVertex[0], outVertex[1], outVertex[2], fShader);
    }
}

inline void Renderer :: NDC2Screen (Vector4 &pos)
{
    pos.x = (pos.x + 1) * 0.5f * width;
    pos.y = (pos.y + 1) * 0.5f * height;
    pos.z = pos.w;
    pos.w = 1.0f / pos.w;
}

inline bool Renderer :: BackFaceCulling (const Vector4 &p0, const Vector4 p1, const Vector4 &p2)
{
    return (p0.Dot ((p1 - p0).Cross (p2 - p0)) >= 0);
}

void Renderer :: FillTriangle (Model &model, const Vertex &v0, const Vertex &v1, const Vertex v2, FShader fShader)
{
    auto PixelShader = [&model, this] (Vertex &v) -> Vector4
    {
        auto ldir = (light.viewPos - v.viewPos).Normalize ();
        auto lambertian = std::max (0.0f, ldir.Dot (v.normal));
        auto specular = 0.0f;
        if (lambertian > 0)
        {
            auto viewDir = (-v.viewPos).Normalize ();
            auto half = (ldir + viewDir).Normalize ();
            auto angle = std::max (0.0f, half.Dot (v.normal));
            specular = pow (angle, 16.0f);
        }
        return (TextureLookup (model.material.texture, v.uv.x, v.uv.y) * (light.ambientColor * model.material.ka + light.diffuseColor * lambertian * model.material.kd) + light.specularColor * specular * model.material.ks);
    };
    
    Vector4 weight = {0, 0, 0, EdgeFunc (v0.pos, v1.pos, v2.pos)};
    int x0 = std::max (0, (int)floor (std::min (v0.pos.x, std::min (v1.pos.x, v2.pos.x))));
    int y0 = std::max (0, (int)floor (std::min (v0.pos.y, std::min (v1.pos.y, v2.pos.y))));
    int x1 = std::min (width - 1, (int)floor (std::max (v0.pos.x, std::max (v1.pos.x, v2.pos.x))));
    int y1 = std::min (height - 1, (int)floor (std::max (v0.pos.y, std::max (v1.pos.y, v2.pos.y))));
    for (int y = y0;y <= y1;y++)
    {
        for (int x = x0;x <= x1;x++)
        {
            Vertex v = {{x + 0.5f, y + 0.5f, 0}};
            if (TriangleCheck(v0, v1, v2, v, weight))continue;
            Interpolate(v0, v1, v2, v, weight);
            if (v.pos.z >= depthBuffer[x + y * width]) continue;
            DrawPoint (x, y, fShader (model, v), v.pos.z);
        }
    }
}

bool Renderer :: TriangleCheck (const Vertex &v0, const Vertex &v1, const Vertex &v2, Vertex &v, Vector4 &w)
{
    w.x = EdgeFunc (v1.pos, v2.pos, v.pos) * v0.pos.w / w.w; // pos.w == 1 / pos.z . we did that in Ndc2Screen()
    w.y = EdgeFunc (v2.pos, v0.pos, v.pos) * v1.pos.w / w.w;
    w.z = EdgeFunc (v0.pos, v1.pos, v.pos) * v2.pos.w / w.w;
    return (w.x < 0 || w.y < 0 || w.z < 0);
}

inline float Renderer :: EdgeFunc (const Vector4 &p0, const Vector4 &p1, const Vector4 &p2)
{
    return ((p2.x - p0.x) * (p1.y - p0.y) - (p2.y - p0.y) * (p1.x - p0.x));
}

inline void Renderer :: Interpolate (const Vertex &v0, const Vertex &v1, const Vertex &v2, Vertex &v, const Vector4 &w)
{
    v.pos.z = 1.0f / (w.x + w.y + w.z);
    v.viewPos = (v0.viewPos * w.x + v1.viewPos * w.y + v2.viewPos * w.z) * v.pos.z;
    v.normal = (v0.normal * w.x + v1.normal * w.y + v2.normal * w.z) * v.pos.z;
    v.color = (v0.color * w.x + v1.color * w.y + v2.color * w.z) * v.pos.z;
    v.uv = (v0.uv * w.x + v1.uv * w.y + v2.uv * w.z) * v.pos.z;
}

inline Vector4 Renderer :: TextureLookup (const Texture &texture, float s, float t)
{
    Vector4 color = { 0.87f, 0.87f, 0.87f, 0 };
    if (!texture.data.empty ())
    {
        s = Saturate (s), t = Saturate (t);
        color = BilinearFiltering (texture, s * (texture.width - 1), t * (texture.height - 1));
    }
    return color;
}

inline float Renderer :: Saturate (float n)
{
    return std::min (1.0f, std::max (0.0f, n));
}

inline Vector4 Renderer :: BilinearFiltering (const Texture &texture, float s, float t)
{
    if (s <= 0.5f || s >= texture.smax) return LinearFilteringV (texture, s, t);
    if (t <= 0.5f || t >= texture.tmax) return LinearFilteringH (texture, s, t);
    float supper = s + 0.5f, fs = std::floor (supper), ws = supper - fs, tupper = t + 0.5f, ts = std::floor (tupper), wt = tupper - ts;
    return (NearestNeighbor (texture, fs, ts) * ws * wt +
            NearestNeighbor (texture, fs, ts - 1.0f) * ws * (1.0f - wt) +
            NearestNeighbor (texture, fs - 1.0f, ts) * (1.0f - ws) * wt +
            NearestNeighbor (texture, fs - 1.0f, ts - 1.0f) * (1.0f - ws) * (1.0f - wt));
}

inline Vector4 Renderer :: LinearFilteringH (const Texture &texture, float s, float t)
{
    if (s <= 0.5f || s >= texture.smax) return NearestNeighbor (texture, s, t);
    float supper = s + 0.5f, fs = std::floor (supper), ws = supper - fs;
    return (NearestNeighbor (texture, fs, t) * ws + NearestNeighbor (texture, fs - 1.0f, t) * (1.0f - ws));
}

inline Vector4 Renderer :: LinearFilteringV (const Texture &texture, float s, float t)
{
    if (t <= 0.5f || t >= texture.tmax) return NearestNeighbor (texture, s, t);
    float tupper = t + 0.5f, ts = std::floor (tupper), wt = tupper - ts;
    return (NearestNeighbor (texture, s, ts) * wt + NearestNeighbor (texture, s, ts - 1.0f) * (1.0f - wt));
}

inline Vector4 Renderer :: NearestNeighbor (const Texture &texture, float s, float t)
{
    return texture.data[(int)std::round (s) + (int)std::round (t) * texture.width];
}

void Renderer :: DrawTriangle (const Vertex &v0, const Vertex &v1, const Vertex &v2, const Vector4 &color)
{
    DrawLine (v0.pos, v1.pos, color); DrawLine (v1.pos, v2.pos, color); DrawLine (v0.pos, v2.pos, color);
}

void Renderer :: DrawLine (const Vector4 &p0, const Vector4 &p1, const Vector4 &color)
{
    int x0 = (int)std::floor (p0.x), x1 = (int)std::floor (p1.x), y0 = (int)std::floor (p0.y), y1 = (int)std::floor (p1.y);
    if (abs (x1 - x0) >= abs (y1 - y0))
    {
        if (x0 > x1) { std::swap (x0, x1); std::swap (y0, y1); }
        DrawLineInternal (x0, y0, x1, y1, color, false);
    }
    else
    {
        if (y0 > y1) { std::swap (x0, x1); std::swap (y0, y1); }
        DrawLineInternal (y0, x0, y1, x1, color, true);
    }
}

void Renderer :: DrawLineInternal (int x0, int y0, int x1, int y1, const Vector4 &color, bool steep)
{
    if (y0 == y1)
    {
        for (int x = x0, y = y0; x <= x1; x++)
            steep ? DrawPoint (y, x, color, 0) : DrawPoint (x, y, color, 0);
        return;
    }
    int dx = x1 - x0, dy = abs (y1 - y0), ystep = dy / (y1 - y0), delta = dy - dx, y = y0;
    for (int x = x0; x <= x1; x++, delta += dy)
    {
        steep ? DrawPoint (y, x, color, 0) : DrawPoint (x, y, color, 0);
        if (delta >= 0)
        {
            y += ystep;
            delta -= dx;
        }
    }

}

void Renderer :: DrawPoint (int x, int y, const Vector4 &color, float z)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        frameBuffer[x + y * width] = color; // write frame buffer
        depthBuffer[x + y * width] = z; // write z buffer
    }
}

void Renderer :: AddModel(const Model &mod)
{
	modelList.push_back(mod);
}

void Renderer :: DrawAllModels()
{
    for (std::vector<Model> :: iterator i = modelList.begin();i != modelList.end();i++)
	{
		DrawModel(*i, NULL, NULL);
	}
}

void Renderer :: DrawAllModelsWithSpecifiedShaders(VShader vShader, FShader fShader)
{
	
}

Texture Renderer :: GenerateDepthMap()
{
	//DrawAllModelsWithSpecifiedShaders(VertexShaderDepth, FragmentShaderDepth);
	return Texture();
}
