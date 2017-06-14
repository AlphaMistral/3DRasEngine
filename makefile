

RasEngine : src/main.cpp

	g++ -o RasEngine -I src/Math/ -I src/Model/ -I src/Render/ -I src/Util/ -I src/Trans/ -I src/ src/main.cpp src/Math/EulerAngles.cpp src/Math/Matrix.cpp src/Math/Quaternion.cpp src/Math/RotationMatrix.cpp src/Math/Vector.cpp src/Model/Mesh.cpp src/Model/Model.cpp src/Math/RasTransform.cpp src/Render/Renderer.cpp src/Render/ShaderLab.cpp src/Util/BMPManager.cpp src/Util/Light.cpp src/Util/ObjectProperties.cpp --std=c++11 -O2 -Wall src/Render/Material.cpp 