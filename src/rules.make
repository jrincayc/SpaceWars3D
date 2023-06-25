CXX = g++
#DEBUG_FLAGS = -O2 -pg
#DEBUG_FLAGS = -O2 
DEBUG_FLAGS = -g 
CXXFLAGS = -Wall -I../utility -I../physics -I../graphics -I../resources -I../input -I/usr/local/xerces/include $(DEBUG_FLAGS)
LDFLAGS = -L/usr/local/xerces/lib -lxerces-c -lGL -lGLU -lglut -lSDL $(DEBUG_FLAGS)
