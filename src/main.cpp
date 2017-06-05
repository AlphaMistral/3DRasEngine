#include <iostream>
#include "Renderer.hpp"
#include "ShaderProperty.hpp"

int main ()
{
    const int WIDTH = 1024, HEIGHT = 768;
    Renderer renderer (WIDTH, HEIGHT);
    
    renderer.SetFrustum ((float)M_PI_2, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    renderer.SetCamera (Vector4( 0.0f, 3.0f, 5.0f ), Vector4( 0.0f, 0.0f, 0.0f ));
    renderer.SetLight (Vector4( -10.0f, 30.0f, 30.0f ), Vector4( 0.5f, 0.0f, 0.0f, 0 ), Vector4( 0.8f, 0.8f, 0.8f, 0 ), Vector4( 0.5f, 0.5f, 0.5f, 0 ));
    Vector3 eulerAngles = Vector3(0, acos(-1) / 10, 0);
	UniformBlinnPhong *bunnyMat = new UniformBlinnPhong(0.1f, 0.8f, 0.7f, "res/bunny.bmp");
	UniformBlinnPhong *sphereMat = new UniformBlinnPhong(0.1f, 1.0f, 0.5f, "res/sphere.bmp");
	UniformBlinnPhong *cubeMat = new UniformBlinnPhong(0.5f, 0.8f, 0.8f, "res/cube.bmp");
    Quaternion q = Quaternion :: GetQuaternionFromEulerAngles(eulerAngles);
	VShader xxx = &ShaderLab::VertexShader;
	FShader fff = &ShaderLab::FragmentBlinnPhong;
    Model sphere ("res/sphere", Vector4( 2.5f, 0.5f, 1.5f ));
	sphere.uniform = sphereMat;
    renderer.DrawModel (sphere, xxx, fff);
    Model bunny ("res/bunny", Vector4( 0.0f, 0.0f, 0.0f ));
	bunny.uniform = bunnyMat;
    renderer.DrawModel (bunny, xxx, fff);
    Model cube ("res/cube", Vector4( -2.0f, 0.0f, 2.0f ));
    RasTransform :: RotateMatrixByQuaternion(cube.worldMat, q);
	cube.uniform = cubeMat;
    renderer.DrawModel (cube, xxx, fff);
	
    BMPManager::SaveBMP (renderer.frameBuffer, WIDTH, HEIGHT, "momo.bmp");
    return 0;
}
