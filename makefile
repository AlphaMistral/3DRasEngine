RasEngine: src/main.cpp

	g++ -o RasEngine src/main.cpp src/Renderer.cpp src/RasTransform.cpp src/BMPManager.cpp src/Matrix.cpp src/Mesh.cpp src/Model.cpp src/ObjectProperties.cpp src/Vector.cpp src/Quaternion.cpp src/EulerAngles.cpp src/Light.cpp src/RasMath.cpp src/ShaderProperty.cpp -std=c++11 -O2 -Wall