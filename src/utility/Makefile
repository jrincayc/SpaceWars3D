include ../rules.make


all : Vector3D.o Affine.o Point3D.o Quaternion.o DirectoryIterator.o Preferences.o Utility.o

clean :
	rm -f *~ *.o



Vector3D.o : Vector3D.h Vector3D.cpp
	$(CXX) $(CXXFLAGS) -c Vector3D.cpp

Affine.o : Affine.cpp Affine.h 
	$(CXX) $(CXXFLAGS) -c $<

Point3D.o : Point3D.cpp Point3D.h 
	$(CXX) $(CXXFLAGS) -c $<

Quaternion.o : Quaternion.cpp Quaternion.h  Vector3D.h Point3D.h
	$(CXX) $(CXXFLAGS) -c $<

DirectoryIterator.o : DirectoryIterator.cpp DirectoryIterator.h 
	$(CXX) $(CXXFLAGS) -c $<

Preferences.o : Preferences.cpp Preferences.h 
	$(CXX) $(CXXFLAGS) -c $<

Utility.o : Utility.cpp Utility.h 
	$(CXX) $(CXXFLAGS) -c $<

