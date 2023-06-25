include ../rules.make


all : spacewars3d

clean :
	rm -f *~ *.o


spacewars3d : main.o ../graphics/Camera.o            ../resources/Planet.o ../graphics/Canvas.o            ../resources/ResourceManager.o ../graphics/DirectionalLight.o  ../resources/Resource.o ../graphics/LightManager.o      ../resources/Ship.o ../graphics/Light.o             ../resources/SolarMap.o ../graphics/Material.o          ../resources/Sun.o ../graphics/PointLight.o        ../resources/Texture.o ../input/PlayerInput.o          ../utility/Affine.o ../input/ShipInput.o            ../utility/DirectoryIterator.o ../physics/Object.o             ../utility/Point3D.o ../physics/ODE.o                ../utility/Preferences.o ../physics/PoweredObject.o      ../utility/Quaternion.o ../physics/Universe.o           ../utility/Utility.o ../resources/Mesh.o             ../utility/Vector3D.o ../physics/Bomb.o
	$(CXX) $(LDFLAGS) -o spacewars3d main.o ../utility/*.o ../physics/*.o ../graphics/*.o ../resources/*.o ../input/*.o 

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c $<



