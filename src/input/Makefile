include ../rules.make


all : PlayerInput.o ShipInput.o

clean :
	rm -f *~ *.o



PlayerInput.o : PlayerInput.cpp PlayerInput.h
	$(CXX) $(CXXFLAGS) -c $<

ShipInput.o : ShipInput.cpp ShipInput.h
	$(CXX) $(CXXFLAGS) -c $<




