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
    Vector3 eulerAngles = Vector3(0, acos(-1) / 6, 0);
    Quaternion q = Quaternion :: GetQuaternionFromEulerAngles(eulerAngles);
    Model sphere ("res/sphere", { 2.5f, 0.5f, 1.5f }, { 0.1f, 1.0f, 0.5f });
	VShader xxx = &ShaderLab::VertexShader;
	FShader fff = &ShaderLab::FragmentBlinnPhong;
    renderer.DrawModel (sphere, xxx, fff);
    Model bunny ("res/bunny", { 0.0f, 0.0f, 0.0f }, { 0.1f, 0.8f, 0.7f });
    renderer.DrawModel (bunny, xxx, fff);
    Model cube ("res/cube", { -2.0f, 0.0f, 2.0f }, { 0.3f, 0.8f, 0.8f });
    RasTransform :: RotateMatrixByQuaternion(cube.worldMat, q);
    renderer.DrawModel (cube, xxx, fff);
    //Model cubeFrame ("res/cube", { 4.0f, 1.8f, -2.2f }, { 0.5f, 0.8f, 0.8f });
    //renderer.DrawModel (cubeFrame, false, true);
	
    BMPManager::SaveBMP (renderer.frameBuffer, WIDTH, HEIGHT, "momo.bmp");
    return 0;
}
