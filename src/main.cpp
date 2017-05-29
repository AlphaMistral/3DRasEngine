#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"

using namespace std;

int main ()
{
    cout << "Fuck World!" << endl;
    Vector4 vec(1.0, 1.4, 1.5, 1.0);
    Vector4 vec1(4.4, 1.1, 1.1, 1.0);
    cout << vec.Cross(vec1).x << endl;
    Matrix4x4 mat1, mat2;
    cout << mat1.InvertTranspose().m[0][2] << endl;
    return 0;
}
