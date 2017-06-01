#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "RasTransform.hpp"
#include "Model.hpp"
#include "Renderer.hpp"

using namespace std;

int main ()
{
    const int WIDTH = 1024, HEIGHT = 768;
    Renderer renderer (WIDTH, HEIGHT);
    
    renderer.SetFrustum ((float)M_PI_2, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    renderer.SetCamera ({ 0.0f, 3.0f, 5.0f }, { 0.0f, 0.0f, 0.0f });
    renderer.SetLight ({ -10.0f, 30.0f, 30.0f }, { 0.5f, 0.0f, 0.0f, 0 }, { 0.8f, 0.8f, 0.8f, 0 }, { 0.5f, 0.5f, 0.5f, 0 });
    
    // Model (filepath, position, material)
    Model sphere ("res/sphere", { 2.5f, 0.5f, 1.5f }, { 0.1f, 1.0f, 0.5f });
    renderer.DrawModel (sphere, true, false);
    Model bunny ("res/bunny", { 0.0f, 0.0f, 0.0f }, { 0.1f, 0.8f, 0.7f });
    renderer.DrawModel (bunny, true, false);
    Model cube ("res/cube", { -2.0f, 0.0f, 2.0f }, { 0.3f, 0.8f, 0.8f });
    cube.worldMat = RasTransform :: ScaleMatrix(cube.worldMat, 2, 2, 2);
    cube.worldMat = RasTransform :: RotateMatrixByEuler(cube.worldMat, acos(-1) / 10, 0, 0);
    renderer.DrawModel (cube, true, false);
    Model cubeFrame ("res/cube", { 4.0f, 1.8f, -2.2f }, { 0.5f, 0.8f, 0.8f });
    renderer.DrawModel (cubeFrame, false, true);
    
    // save the frame buffer to a bmp file
    BMPManager::SaveBMP (renderer.frameBuffer, WIDTH, HEIGHT, "momo.bmp");
    return 0;
}
