include ../rules.make


all : Camera.o Canvas.o DirectionalLight.o Light.o LightManager.o Material.o PointLight.o StarField.o

clean :
	rm -f *~ *.o



Camera.o : Camera.cpp Camera.h
	$(CXX) $(CXXFLAGS) -c $<

Canvas.o : Canvas.cpp Canvas.h
	$(CXX) $(CXXFLAGS) -c $<

DirectionalLight.o : DirectionalLight.cpp DirectionalLight.h
	$(CXX) $(CXXFLAGS) -c $<

Light.o : Light.cpp Light.h
	$(CXX) $(CXXFLAGS) -c $<

LightManager.o : LightManager.cpp LightManager.h
	$(CXX) $(CXXFLAGS) -c $<

Material.o : Material.cpp Material.h
	$(CXX) $(CXXFLAGS) -c $<

PointLight.o : PointLight.cpp PointLight.h
	$(CXX) $(CXXFLAGS) -c $<

StarField.o : StarField.cpp StarField.h
	$(CXX) $(CXXFLAGS) -c $<




