OS = $(shell uname)

ifeq ($(OS),Darwin)
    PLATFORM_FLAGS = -DGL_SILENCE_DEPRECATION
    PLATFORM_LIBS = -framework OpenGL
    XERCES_FLAGS = $(shell pkg-config xerces-c --cflags)
    XERCES_LIBS = $(shell pkg-config xerces-c --libs)
else
    PLATFORM_FLAGS = 
    XERCES_FLAGS = -I/usr/local/xerces/include
    XERCES_LIBS = -L/usr/local/xerces/lib -lxerces-c
    PLATFORM_LIBS = -lGL -lGLU -lglut -lSDL
endif

CXX = g++
#DEBUG_FLAGS = -O2 -pg
#DEBUG_FLAGS = -O2 
DEBUG_FLAGS = -g
SDL_FLAGS = $(shell sdl-config --cflags)
SDL_LIBS = $(shell sdl-config --libs)
CXXFLAGS = -std=c++17 -Wall -I../utility -I../physics -I../graphics -I../resources -I../input $(SDL_FLAGS) $(XERCES_FLAGS) $(DEBUG_FLAGS) $(PLATFORM_FLAGS)
LDFLAGS =  $(SDL_LIBS) $(XERCES_LIBS) $(PLATFORM_LIBS) $(DEBUG_FLAGS)
