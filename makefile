INCLUDE = -I include/Math -I include/Render -I include/Util -I include/Model

RasEngine : Math.a Render.a Model.a Util.a src/main.cpp
	g++ -o RasEngine $(INCLUDE) src/main.cpp Math.a Render.a Model.a Util.a --std=c++11 -O2 -Wall

Math.a : src/Math/EulerAngles.cpp src/Math/Matrix.cpp src/Math/Quaternion.cpp src/Math/RotationMatrix.cpp src/Math/Vector.cpp src/Math/RasMath.cpp
	g++ -c $(INCLUDE) src/Math/EulerAngles.cpp src/Math/Matrix.cpp src/Math/Quaternion.cpp src/Math/RotationMatrix.cpp src/Math/Vector.cpp src/Math/RasTransform.cpp src/Math/RasMath.cpp --std=c++11 -O2 -Wall
	ar cr Math.a EulerAngles.o Matrix.o Quaternion.o RotationMatrix.o Vector.o RasTransform.o

Model.a : src/Model/Mesh.cpp src/Model/Model.cpp
	g++ -c $(INCLUDE) src/Model/Mesh.cpp src/Model/Model.cpp --std=c++11 -O2 -Wall
	ar cr Model.a Model.o Mesh.o

Render.a : src/Render/Renderer.cpp src/Render/ShaderLab.cpp src/Render/Material.cpp 
	g++ -c $(INCLUDE) src/Render/Renderer.cpp src/Render/ShaderLab.cpp src/Render/Material.cpp --std=c++11 -O2 -Wall
	ar cr Render.a Renderer.o ShaderLab.o Material.o

Util.a : src/Util/BMPManager.cpp src/Util/Light.cpp src/Util/ObjectProperties.cpp
	g++ -c $(INCLUDE) src/Util/BMPManager.cpp src/Util/Light.cpp src/Util/ObjectProperties.cpp --std=c++11 -O2 -Wall
	ar cr Util.a BMPManager.o Light.o ObjectProperties.o
clean : 
	rm -f *.o *.a

