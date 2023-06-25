include ../rules.make


all : Resource.o ResourceManager.o Sun.o SolarMap.o Planet.o Texture.o Ship.o Mesh.o

clean :
	rm -f *~ *.o



Resource.o : Resource.cpp Resource.h
	$(CXX) $(CXXFLAGS) -c $<

ResourceManager.o : ResourceManager.cpp ResourceManager.h
	$(CXX) $(CXXFLAGS) -c $<

Sun.o : Sun.cpp Sun.h
	$(CXX) $(CXXFLAGS) -c $<

SolarMap.o : SolarMap.cpp SolarMap.h
	$(CXX) $(CXXFLAGS) -c $<

Planet.o : Planet.cpp Planet.h
	$(CXX) $(CXXFLAGS) -c $<

Texture.o : Texture.cpp Texture.h
	$(CXX) $(CXXFLAGS) -c $<

Mesh.o : Mesh.cpp Mesh.h
	$(CXX) $(CXXFLAGS) -c $<

Ship.o : Ship.cpp Ship.h
	$(CXX) $(CXXFLAGS) -c $<



