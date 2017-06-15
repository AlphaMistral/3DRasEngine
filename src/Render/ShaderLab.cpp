//
//  ShaderLab.cpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/6/5.
//  Copyright © 2017年 于京平. All rights reserved.
//

#include "ShaderLab.hpp"

Vector4 ShaderLab :: WORLD_SPACE_LIGHT_POS;
Vector4 ShaderLab :: WORLD_SPACE_CAMERA_POS;
Matrix4x4 ShaderLab :: RAS_MATRIX_M;
Matrix4x4 ShaderLab :: RAS_MATRIX_V;
Matrix4x4 ShaderLab :: RAS_MATRIX_P;
Matrix4x4 ShaderLab :: RAS_MATRIX_VP;
Matrix4x4 ShaderLab :: RAS_MATRIX_MV;
Matrix4x4 ShaderLab :: RAS_MATRIX_MVP;
Matrix4x4 ShaderLab :: RAS_MATRIX_IT_MV;
Vector4 ShaderLab :: WORLD_SPACE_LIGHT_COLOR_AMB;
Vector4 ShaderLab :: WORLD_SPACE_LIGHT_COLOR_DIF;
Vector4 ShaderLab :: WORLD_SPACE_LIGHT_COLOR_SPE;
Matrix4x4 ShaderLab :: WORLD_SPACE_LIGHT_V;
Matrix4x4 ShaderLab :: WORLD_SPACE_LIGHT_VP;
Texture ShaderLab :: WORLD_SPACE_LIGHT_SHADOWMAP;

float ShaderLab :: DEPTH_OFFSET = 0.0001f;

static Vector4 PROJECTION_PARAMS;

Vertex ShaderLab :: VertexShader(const VertexInput &inVertex)
{
    Vertex outVertex;
    outVertex.pos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MVP);
	outVertex.worldPos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_M * WORLD_SPACE_LIGHT_VP);
    outVertex.viewPos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MV);
    outVertex.normal = RasTransform :: TransformDir(inVertex.normal, RAS_MATRIX_IT_MV).Normalize ();
    outVertex.uv = inVertex.uv;
    return outVertex;
}

Vertex ShaderLab :: VertexShaderSimple(const VertexInput &inVertex)
{
	Vertex outVertex;
	outVertex.pos = RasTransform :: TransformPoint(inVertex.pos, RAS_MATRIX_MVP);
	return outVertex;
}

Vector4 ShaderLab :: FragmentDepth(const Uniform *uni, const Vertex &i)
{
	float depth = i.pos.z;
    return Vector4(depth, depth, depth, 1.0f);
}

Vector4 ShaderLab :: FragmentBlinnPhong(const Uniform *uni, const Vertex &v)
{
    const UniformBlinnPhong *uniform = static_cast<const UniformBlinnPhong*>(uni);
    auto lightView = RasTransform :: TransformPoint(WORLD_SPACE_LIGHT_POS, RAS_MATRIX_V);
    auto ldir = (lightView - v.viewPos).Normalize ();
    auto lambertian = std::max (0.0f, ldir.Dot (v.normal));
    auto specular = 0.0f;
	float shadowed = 0;
	float projX, projY, projZ;
	projX = v.worldPos.x * 0.5 + 0.5;
	projY = v.worldPos.y * 0.5 + 0.5;
	projZ = v.worldPos.z * 0.5 + 0.5;
	float result = TextureLookup(WORLD_SPACE_LIGHT_SHADOWMAP, projX, projY).x;
	if (result + DEPTH_OFFSET > projZ)
		shadowed = 1;
    if (lambertian > 1)
    {
        auto viewDir = (-v.viewPos).Normalize ();
        auto half = (ldir + viewDir).Normalize ();
        auto angle = std::max (0.0f, half.Dot (v.normal));
        specular = pow (angle, 16.0f);
    }
	Vector4 color = (TextureLookup (uniform->texture, v.uv.x, v.uv.y) * (WORLD_SPACE_LIGHT_COLOR_AMB * uniform->ka + WORLD_SPACE_LIGHT_COLOR_DIF * lambertian * uniform->kd * shadowed) + WORLD_SPACE_LIGHT_COLOR_SPE * shadowed * specular * uniform->ks);
	color.w = 1;
    return color;
}

inline Vector4 ShaderLab :: TextureLookup (const Texture &texture, float s, float t)
{
    Vector4 color = { 0.87f, 0.87f, 0.87f, 1 };
    if (!texture.data.empty ())
    {
        s = Saturate (s), t = Saturate (t);
        color = BilinearFiltering (texture, s * (texture.width - 1), t * (texture.height - 1));
    }
	color.w = 1;
    return color;
}

inline float ShaderLab :: Saturate (float n)
{
    return std::min (1.0f, std::max (0.0f, n));
}

inline Vector4 ShaderLab :: BilinearFiltering (const Texture &texture, float s, float t)
{
    if (s <= 0.5f || s >= texture.smax) return LinearFilteringV (texture, s, t);
    if (t <= 0.5f || t >= texture.tmax) return LinearFilteringH (texture, s, t);
    float supper = s + 0.5f, fs = std::floor (supper), ws = supper - fs, tupper = t + 0.5f, ts = std::floor (tupper), wt = tupper - ts;
    return (NearestNeighbor (texture, fs, ts) * ws * wt +
            NearestNeighbor (texture, fs, ts - 1.0f) * ws * (1.0f - wt) +
            NearestNeighbor (texture, fs - 1.0f, ts) * (1.0f - ws) * wt +
            NearestNeighbor (texture, fs - 1.0f, ts - 1.0f) * (1.0f - ws) * (1.0f - wt));
}

inline Vector4 ShaderLab :: LinearFilteringH (const Texture &texture, float s, float t)
{
    if (s <= 0.5f || s >= texture.smax) return NearestNeighbor (texture, s, t);
    float supper = s + 0.5f, fs = std::floor (supper), ws = supper - fs;
    return (NearestNeighbor (texture, fs, t) * ws + NearestNeighbor (texture, fs - 1.0f, t) * (1.0f - ws));
}

inline Vector4 ShaderLab :: LinearFilteringV (const Texture &texture, float s, float t)
{
    if (t <= 0.5f || t >= texture.tmax) return NearestNeighbor (texture, s, t);
    float tupper = t + 0.5f, ts = std::floor (tupper), wt = tupper - ts;
    return (NearestNeighbor (texture, s, ts) * wt + NearestNeighbor (texture, s, ts - 1.0f) * (1.0f - wt));
}

inline Vector4 ShaderLab :: NearestNeighbor (const Texture &texture, float s, float t)
{
    return texture.data[(int)std::round (s) + (int)std::round (t) * texture.width];
}

