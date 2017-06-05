#include <iostream>
#include "Renderer.hpp"
#include "ShaderProperty.hpp"

int main ()
{
    const int WIDTH = 1024, HEIGHT = 768;
    Renderer renderer (WIDTH, HEIGHT);
    
    renderer.SetFrustum ((float)M_PI_2, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    renderer.SetCamera ({ 0.0f, 3.0f, 5.0f }, { 0.0f, 0.0f, 0.0f });
    renderer.SetLight ({ -10.0f, 30.0f, 30.0f }, { 0.5f, 0.0f, 0.0f, 0 }, { 0.8f, 0.8f, 0.8f, 0 }, { 0.5f, 0.5f, 0.5f, 0 });
    Vector3 eulerAngles = Vector3(0, acos(-1) / 10, 0);
	UniformBlinnPhong *bunnyMat = new UniformBlinnPhong(0.1f, 0.8f, 0.7f, "res/bunny.bmp");
    Quaternion q = Quaternion :: GetQuaternionFromEulerAngles(eulerAngles);
    Model sphere ("res/sphere", { 2.5f, 0.5f, 1.5f });
	VShader xxx = &ShaderLab::VertexShader;
	FShader fff = &ShaderLab::FragmentBlinnPhong;
    //renderer.DrawModel (sphere, xxx, fff);
    Model bunny ("res/bunny", { 0.0f, 0.0f, 0.0f });
	bunny.uniform = bunnyMat;
    renderer.DrawModel (bunny, xxx, fff);
    Model cube ("res/cube", { -2.0f, 0.0f, 2.0f });
    RasTransform :: RotateMatrixByQuaternion(cube.worldMat, q);
    //renderer.DrawModel (cube, xxx, fff);
	
    BMPManager::SaveBMP (renderer.frameBuffer, WIDTH, HEIGHT, "momo.bmp");
    return 0;
}
