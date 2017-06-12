//
//  Renderer.hpp
//  3DRasEngine
//
//  Created by 于京平 on 2017/5/29.
//  Copyright © 2017年 于京平. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

#include "ShaderLab.hpp"
#include "RenderObject.hpp"

class Renderer
{
public:
    int width, height;
    std::vector <Vector4> frameBuffer;
    std::vector <float> depthBuffer;
    std::vector <RenderObject> modelList;
    Matrix4x4 proj, view, mv, mvp, nmv;
    Light light;
	ShaderLab shaderLab;
	
    Renderer (int w, int h);
    
    void SetFrustum (float fov, float aspr, float np, float fp);
    void SetCamera (const Vector4 &look, const Vector4 &at);
    void SetLight (const Vector4 &pos, const Vector4 &ambi, const Vector4 &diff, const Vector4 &spec);
    //void DrawModel (Model &model, bool drawTex = true, bool drawWireFrame = false);
	void DrawModel (const RenderObject &, VShader, FShader);
	void DrawModel (const Model &, const Uniform *);
	void DrawAllModels ();
	void DrawAllModelsWithSpecifiedShaders (VShader, FShader);
	void GenerateShadowMap (const int, const int);
	
	void SetupProperties ();
	
	void AddModel (const RenderObject &mod);
	
    inline void NDC2Screen (Vector4 &pos);
    
    static inline bool BackFaceCulling (const Vector4 &p0, const Vector4 p1, const Vector4 &p2);
    
    void FillTriangle (const Uniform *material, const Vertex &v0, const Vertex &v1, const Vertex v2, FShader);
    
    static bool TriangleCheck (const Vertex &v0, const Vertex &v1, const Vertex &v2, Vertex &v, Vector4 &w);
    
    static inline float EdgeFunc (const Vector4 &p0, const Vector4 &p1, const Vector4 &p2);
    
    static inline void Interpolate (const Vertex &v0, const Vertex &v1, const Vertex &v2, Vertex &v, const Vector4 &w);
    
    static inline Vector4 TextureLookup (const Texture &texture, float s, float t);
    
    static inline float Saturate (float n);
    
    static inline Vector4 BilinearFiltering (const Texture &texture, float s, float t);
    
    static inline Vector4 LinearFilteringH (const Texture &texture, float s, float t);
    
    static inline Vector4 LinearFilteringV (const Texture &texture, float s, float t);
    
    static inline Vector4 NearestNeighbor (const Texture &texture, float s, float t);
    
    void DrawTriangle (const Vertex &v0, const Vertex &v1, const Vertex &v2, const Vector4 &color);
    
    void DrawLine (const Vector4 &p0, const Vector4 &p1, const Vector4 &color);
    
    void DrawLineInternal (int x0, int y0, int x1, int y1, const Vector4 &color, bool steep);
    
    void DrawPoint (int x, int y, const Vector4 &color, float z);
};

#endif /* Renderer_hpp */
