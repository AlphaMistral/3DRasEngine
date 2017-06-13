#include <iostream>
#include "Renderer.hpp"

int main ()
{
    const int WIDTH = 1024 * 2, HEIGHT = 768 * 2;
    Renderer renderer (WIDTH, HEIGHT);
    
    renderer.SetFrustum ((float)M_PI_2, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    renderer.SetCamera (Vector4( 0.0f, 3.0f, 5.0f ), Vector4( 0.0f, 0.0f, 0.0f ));
    renderer.SetLight (Vector4( -2.0f, 6.0f, 6.0f ), Vector4( 0.5f, 0.0f, 0.0f, 0 ), Vector4( 0.8f, 0.8f, 0.8f, 0 ), Vector4( 0.5f, 0.5f, 0.5f, 0 ));
    Vector3 eulerAngles = Vector3(0, acos(-1) / 10, 0);
	UniformBlinnPhong *bunnyMat = new UniformBlinnPhong(0.1f, 0.8f, 0.7f, "res/bunny.bmp");
	UniformBlinnPhong *sphereMat = new UniformBlinnPhong(0.1f, 1.0f, 0.5f, "res/sphere.bmp");
	UniformBlinnPhong *cubeMat = new UniformBlinnPhong(0.5f, 0.8f, 0.8f, "res/cube.bmp");
    Quaternion q = Quaternion :: GetQuaternionFromEulerAngles(eulerAngles);
	VShader xxx = &ShaderLab::VertexShader;
	FShader fff = &ShaderLab::FragmentBlinnPhong;
    Model sphere ("res/sphere", Vector4( -2.0f, 3.5f, 4.5f ));
	sphere.uniform = sphereMat;
	RenderObject sphereRender = RenderObject(sphere, sphereMat);
    Model bunny ("res/bunny", Vector4( 0.0f, 0.0f, 0.0f ));
	RenderObject bunnyRender = RenderObject(bunny, bunnyMat);
	bunny.uniform = bunnyMat;
    Model cube ("res/cube", Vector4( -2.0f, 0.0f, 2.0f ));
	RenderObject cubeRender = RenderObject(cube, cubeMat);
    RasTransform :: RotateMatrixByQuaternion(cube.worldMat, q);
	cube.uniform = cubeMat;
	renderer.AddModel(sphereRender);
	renderer.AddModel(bunnyRender);
	renderer.AddModel(cubeRender);
	renderer.GenerateShadowMap(1024 * 2, 768 * 2);
	//renderer.DrawModel (cubeRender, xxx, fff);
	//renderer.DrawModel (bunnyRender, xxx, fff);
	//renderer.DrawModel (sphereRender, xxx, fff);
	renderer.DrawAllModelsWithSpecifiedShaders(xxx, fff);
    BMPManager::SaveBMP (renderer.frameBuffer, WIDTH, HEIGHT, "momo.bmp");
    return 0;
}
