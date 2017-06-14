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
    modelList = new std::vector<Model> ();
    frameBuffer = new std::vector<Vector4> (w * h, {1.0f, 1.0f, 1.0f, 0});
    depthBuffer = new std::vector<float> (w * h, std::numeric_limits<float> :: max ());
}

Renderer :: ~Renderer ()
{
	delete proj;
	delete view;
	delete mv;
	delete mvp;
	delete nmv;
	delete modelList;
	delete frameBuffer;
	delete depthBuffer;
}

void Renderer :: SetFrustum (float f, float aspr, float np, float fp)
{
	if (proj != NULL)
		delete proj;
	fov = f;
	near = np;
	far = fp;
    proj = new Matrix4x4(RasTransform :: CreateProjectionMatrix (f, aspr, np, fp));
}

void Renderer :: SetCamera (const Vector4 &look, const Vector4 &at)
{
	if (view != NULL)
		delete view;
    view = new Matrix4x4(RasTransform :: CreateViewMatrix(look, at, {0.0f, 1.0f, 0.0f}));
}

void Renderer :: SetLight (const Vector4 &pos, const Vector4 &ambi, const Vector4 &diff, const Vector4 &spec)
{
    light.pos = pos;
    light.ambientColor = ambi;
    light.diffuseColor = diff;
    light.specularColor = spec;
	
	Matrix4x4 rotMat = RasTransform :: CreateRotationMatrixFromEulerAngles(Vector3(-acos(-1) / 3, acos(-1) / 1, 0.0f));
	
	rotMat = RasTransform :: CreateViewMatrix(light.pos, Vector4(0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f));
	
	light.rotMat = RasTransform :: CreateTranslationMatrix(Vector3(pos.x, pos.y, pos.z)) * rotMat;
	
	light.rotMat = rotMat;

	ShaderLab :: WORLD_SPACE_LIGHT_POS = light.pos;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_AMB = light.ambientColor;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_DIF = light.diffuseColor;
	ShaderLab :: WORLD_SPACE_LIGHT_COLOR_SPE = light.specularColor;
}

void Renderer :: DrawModel(const Model &mod, const Material &mat)
{
	ShaderLab :: RAS_MATRIX_M = mod.worldMat;
    ShaderLab :: RAS_MATRIX_V = *view;
	ShaderLab :: RAS_MATRIX_P = *proj;
	ShaderLab :: RAS_MATRIX_MV = (mod.worldMat) * (*view);
	ShaderLab :: RAS_MATRIX_MVP = ShaderLab :: RAS_MATRIX_MV * *proj;
	ShaderLab :: RAS_MATRIX_IT_MV = ShaderLab :: RAS_MATRIX_MV.InvertTranspose();
    for (auto &idx : mod.index)
    {
        Vertex outVertex[3];
        bool badTriangle = false;
        for (int i = 0;i < 3;i++)
        {
			outVertex[i] = mat.vertexShader (VertexInput(mod.vertex[idx.pos[i]], mod.normal[idx.normal[i]], mod.uv[idx.uv[i]]));
            if (outVertex[i].pos.z < 0.0f || outVertex[i].pos.z > 1.0f)
            {
                badTriangle = true;
                break;
            }
            NDC2Screen (outVertex[i].pos);
        }
        if (badTriangle || BackFaceCulling(outVertex[0].viewPos, outVertex[1].viewPos, outVertex[2].viewPos))continue;
        FillTriangle(mat.uniform, outVertex[0], outVertex[1], outVertex[2], mat.fragmentShader);
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

void Renderer :: FillTriangle (const Uniform *material, const Vertex &v0, const Vertex &v1, const Vertex v2, FShader fShader)
{
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
            if (v.pos.z >= (*depthBuffer)[x + y * width]) continue;
            DrawPoint (x, y, fShader (material, v), v.pos.z);
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
	v.worldPos = (v0.worldPos * w.x + v1.worldPos * w.y + v2.worldPos * w.z) * v.pos.z;
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
        (*frameBuffer)[x + y * width] = color; // write frame buffer
        (*depthBuffer)[x + y * width] = z; // write z buffer
    }
}

void Renderer :: AddModel(const Model &mod)
{
	modelList->push_back(mod);
}

void Renderer :: DrawAllModels()
{
    for (std::vector<Model> :: iterator i = modelList->begin();i != modelList->end();i++)
	{
		//DrawModel(*i, NULL, NULL);
	}
}

void Renderer :: DrawAllModelsWithSpecifiedMaterial(const Material &mat)
{
	for (std::vector<Model> :: iterator i = modelList->begin();i != modelList->end();i++)
	{
		DrawModel(*i, mat);
	}
}

///This function now is extremely extremely slow!!!!!!!!!!!
///To be revised in the later version.
void Renderer :: GenerateShadowMap(const int w, const int h, const float fov, const float np, const float fp)
{
	///Claim Backup Storage Variables
	int oldW = width;
	int oldH = height;
	Matrix4x4 *oldView = view;
	Matrix4x4 *oldProj = proj;
	std::vector<Vector4> *oldFrameBuffer = frameBuffer;
	std::vector<float> *oldDepthBuffer = depthBuffer;
	///Claim Backup Storage Variables
	
	///Bind to new Buffer
    std::vector<Vector4> *thisFrameBuffer = new std::vector<Vector4> (w * h, {1.0f, 1.0f, 1.0f, 0});
    std::vector<float> *thisDepthBuffer = new std::vector<float> (w * h, std::numeric_limits<float> :: max ());
    
    frameBuffer = thisFrameBuffer;
    depthBuffer = thisDepthBuffer;
    ///Bind to new Buffer
	
	///Set Frustum Parameters
	width = w;
	height = h;
	///Set Frustum Parameters
	
	///Bind to new Transformation Matrices
	view = &light.rotMat;
    
    Matrix4x4 *thisProj = new Matrix4x4(RasTransform :: CreateProjectionMatrix(fov, w * 1.0 / h, np, fp));
	
    proj = thisProj;
	///Bind to new Transformation Matrices
    
	ShaderLab :: WORLD_SPACE_LIGHT_VP = (*view) * (*proj);
	
	VShader v = &ShaderLab :: VertexShader;
	FShader f = &ShaderLab :: FragmentDepth;
	
	Uniform *depthUni = new Uniform();
	Material depthMateiral = Material(depthUni, v, f);
	DrawAllModelsWithSpecifiedMaterial(depthMateiral);
	
	Texture shadowMap;
	shadowMap.width = w;
	shadowMap.height = h;
	shadowMap.data.resize(w * h);
	
	for (int i = 0;i < w;i++)
	{
		for (int j = 0;j < h;j++)
		{
			float d = (*frameBuffer)[i + j * w].x;
			if (d == 1)
				d = far;
			float value = -(far + near) / (far - near) + (2 * far * near) / (far - near) / d;
			value = (value + 1) / 2;
			value = 1 - value;
			shadowMap.data[i + j * w] = Vector4(value, value, value, 1.0f);
		}
	}
	
	///Restore the Backup Variables
	width = oldW;
	height = oldH;
	view = oldView;
	proj = oldProj;
	frameBuffer = oldFrameBuffer;
	depthBuffer = oldDepthBuffer;
	///Restore the Backup Variables
	
	ShaderLab :: WORLD_SPACE_LIGHT_SHADOWMAP = shadowMap;
	BMPManager::SaveBMP (shadowMap.data, w, h, "results/shadowMap.bmp");
    
    delete thisFrameBuffer;
    delete thisDepthBuffer;
    delete thisProj;
	delete depthUni;
}
