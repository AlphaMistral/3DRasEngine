#include <iostream>
#include "Vector.hpp"
using namespace std;

int main ()
{
    cout << "Fuck World!" << endl;
    Vector4 vec(1.0, 1.4, 1.5, 1.0);
    Vector4 vec1(4.4, 1.1, 1.1, 1.0);
    cout << vec.Cross(vec1).x << endl;
    return 0;
}
