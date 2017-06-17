#include <iostream>
#include "Renderer.hpp"

int main ()
{
	const int WIDTH = 1024, HEIGHT = 768;
	Renderer renderer (WIDTH, HEIGHT);
	
	renderer.SetFrustum ((float)M_PI_2, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	renderer.SetCamera (Vector4( 0.0f, 3.0f, 5.0f ), Vector4( 0.0f, 0.0f, 0.0f ));
	renderer.SetLight (Vector4( -4.0f, 12.0f, 12.0f ), Vector4( 0.5f, 0.0f, 0.0f, 1 ), Vector4( 0.8f, 0.8f, 0.8f, 1 ), Vector4( 0.5f, 0.5f, 0.5f, 1 ));
	Vector3 eulerAngles = Vector3(0, acos(-1) / 10, 0);
	UniformBlinnPhong *bunnyMat = new UniformBlinnPhong(0.1f, 0.8f, 0.7f, "res/bunny.bmp");
	UniformBlinnPhong *sphereMat = new UniformBlinnPhong(0.1f, 1.0f, 0.5f, "res/sphere.bmp");
	UniformBlinnPhong *cubeMat = new UniformBlinnPhong(0.5f, 0.8f, 0.8f, "res/cube.bmp");
	UniformTransparentShield *transMat = new UniformTransparentShield(Vector4(1.0f / 256 * 187, 1.0f / 256 * 245, 1.0f / 256 * 246, 1.0f));
	UniformTransparentShield *largeMat = new UniformTransparentShield(Vector4(1.0f / 256 * 199, 1.0f / 256 * 159, 1.0f / 256 * 150));
	Quaternion q = Quaternion :: GetQuaternionFromEulerAngles(eulerAngles);
	VShader xxx = &ShaderLab::VertexShader;
    FShader fff = &ShaderLab::FragmentBlinnPhong;
	FShader ttt = &ShaderLab::FragmentTransparentShield;
	Model sphere ("res/sphere", Vector4( -2.0f, 3.2f, 4.2f ));
	sphere.uniform = sphereMat;
	Model bunny ("res/bunny", Vector4( 0.0f, 0.0f, 0.0f ));
	bunny.uniform = bunnyMat;
	Model cube ("res/cube", Vector4( -2.0f, 0.0f, 2.0f ));
	Model cubeTrans ("res/cube", Vector4(-0.5f, 1.0f, 2.0f));
	Model cubeLargeTrans ("res/cube", Vector4(-0.5f, 1.0f, 2.0f));
	RasTransform :: RotateMatrixByQuaternion(cube.worldMat, q);
	cube.uniform = cubeMat;
	//Only the models below cast shadow ...
	renderer.AddModel(sphere);
	renderer.AddModel(bunny);
	renderer.AddModel(cube);
	///Only the models above cast shadow ...
	renderer.GenerateShadowMap(1024, 768, (float)M_PI_2, 0.1f, 1000.0f);
	Material cubeMaterial = Material(cubeMat, xxx, fff);
	Material bunnyMaterial = Material(bunnyMat, xxx, fff);
	Material sphereMaterial = Material(sphereMat, xxx, fff);
	Material transMaterial = Material(transMat, xxx, ttt);
	Material largeMaterial = Material(largeMat, xxx, ttt);
	RasTransform :: ScaleMatrix(cubeLargeTrans.worldMat, Vector3(2.0f, 2.0f, 2.0f));
	renderer.DrawModel (bunny, bunnyMaterial);
	renderer.DrawModel (cube, cubeMaterial);
	renderer.DrawModel (sphere, sphereMaterial);
	renderer.DrawModel (cubeTrans, transMaterial);
	renderer.DrawModel (cubeLargeTrans, largeMaterial);
	BMPManager::SaveBMP (*renderer.frameBuffer, WIDTH, HEIGHT, "results/RenderResult.bmp");
	delete bunnyMat;
	delete sphereMat;
	delete cubeMat;
	delete transMat;
	delete largeMat;
    return 0;
}
