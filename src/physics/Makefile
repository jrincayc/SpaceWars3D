include ../rules.make

all : ODE.o Object.o Universe.o PoweredObject.o Bomb.o

clean :
	rm -f *~ *.o


ODE.o : ODE.cpp ODE.h ../utility/Vector3D.h
	$(CXX) $(CXXFLAGS) -c ODE.cpp

Object.o : Object.cpp Object.h ../utility/Vector3D.h ../utility/Point3D.h ../utility/Quaternion.h
	$(CXX) $(CXXFLAGS) -c Object.cpp 

Universe.o : Universe.cpp Universe.h Object.o ODE.o
	$(CXX) $(CXXFLAGS) -c Universe.cpp

PoweredObject.o : PoweredObject.cpp PoweredObject.h Object.cpp Object.h ../utility/Vector3D.h ../utility/Point3D.h
	$(CXX) $(CXXFLAGS) -c PoweredObject.cpp 


Bomb.o : Bomb.cpp Bomb.h Object.o ../utility/Utility.h
	$(CXX) $(CXXFLAGS) -c $<

UniverseTest : UniverseTest.cpp Universe.o ../utility/Vector3D.o
	$(CXX) $(CXXFLAGS) -c UniverseTest.cpp
	$(CXX) -g -o UniverseTest UniverseTest.o Universe.o Object.o ODE.o ../utility/Vector3D.o

UniverseTest2 : UniverseTest2.cpp Universe.o ../utility/Vector3D.o
	$(CXX) $(CXXFLAGS) -c UniverseTest2.cpp
	$(CXX) -g -o UniverseTest2 UniverseTest2.o Universe.o Object.o ODE.o ../utility/Vector3D.o
