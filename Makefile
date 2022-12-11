###
### Makefile to build Cartwheel library and executables on *nix platforms.
###

## Script variables

# OSTYPE is not set by default on Mac OS X.  Should end up being "darwin"
ifndef OSTYPE
  OSTYPE = $(shell uname -s|awk '{print tolower($$0)}')
  #export OSTYPE
endif

# Linux (default)

# Linking information
FRAMEWORKS = 
GLLIBS = -lGLEW -lGL -lGLU -lglut
MISCLIBS = -lm -lgsl -lgslcblas -lode
LPATH = 

# IPATH tells the compiler where to look for include files.
IPATH = -Iinclude 

# CWLPATH tells the linker where to find libraries for building executables
CWLPATH = -Llib -lcartwheel

# CFLAGS contains flags for the compiler
CFLAGS = -O0 -g -w -fPIC -std=c++11 -fpermissive

# OS X
ifeq "$(OSTYPE)" "darwin"
	FRAMEWORKS = -framework Carbon -framework OpenGL -framework GLUT
	GLLIBS = -lglew
	IPATH = -Iinclude -I/opt/local/include/
	LPATH = -L/opt/local/lib
	CFLAGS = -g -w -fPIC -DdDOUBLE
	LIBRARY_EXT=dylib
	LINK_FLAGS=-dynamiclib -dylib
else
	LIBRARY_EXT=so
	LINK_FLAGS=
endif

# Used to have LPATH in front
LIBS = $(GLLIBS) $(MISCLIBS)

CPP_FILES := $(wildcard src/**/*.cpp)
OBJ_FILES := $(CPP_FILES:.cpp=.o)
DEMO_SRCS := $(wildcard Demos/*.cpp)
DEMO_OBJS := $(DEMO_SRCS:.cpp=.o)
DEMO_EXES := $(DEMO_SRCS:.cpp=.exe)

# C++ compiler
CC = g++
# compiler flags:
# -g	tells the compiler to produce symbolic information that a debugger
#	(like gdb) needs.
# -Wall	tells the compiler to print warnings about pretty much everything.
# -w    Hide all of the warnings because I don't like seeing them

## Target depedencies and make rules

all : library interactControl interface mainControl tomsLogger demos

library : $(OBJ_FILES)
	@if [ ! -e ./lib ]; then mkdir ./lib; fi
	$(CC) -shared $(LINK_FLAGS) $(FRAMEWORKS) $(LPATH) $(LIBS) -o lib/libcartwheel.$(LIBRARY_EXT) $(OBJ_FILES) 

demos : library $(DEMO_EXES)

# The default way to convert .cpp files into .o files.
%.o : %.cpp
	$(CC) $(CFLAGS) $(IPATH) -o $@ -c $<

# The default way to convert .o files into .exe files.
%.exe : %.o
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o $@ $< $(CWLPATH) $(LPATH) $(LIBS)

clean :
	$(RM) src/*.o src/*/*.o lib/libcartwheel.$(LIBRARY_EXT)

interactControl : library
	@if [ ! -e ./bin ]; then mkdir ./bin; fi
	@rm -f ./bin/*
	@rm -f ./Demos/*.exe
	$(CC) $(CFLAGS) $(IPATH) -o src/interactControl.o -c src/interactControl.cpp
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o bin/interactControl src/interactControl.o $(CWLPATH) $(LPATH)  $(LIBS)
	
interface : library
	@if [ ! -e ./bin ]; then mkdir ./bin; fi
	$(CC) $(CFLAGS) $(IPATH) -o src/interface.o -c src/interface.cpp
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o bin/interface src/interface.o $(CWLPATH) $(LPATH) $(LIBS)

mainControl : library
	@if [ ! -e ./bin ]; then mkdir ./bin; fi
	$(CC) $(CFLAGS) $(IPATH) -o src/mainControl.o -c src/mainControl.cpp
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o bin/mainControl src/mainControl.o $(CWLPATH) $(LPATH) $(LIBS)

tomsLogger : library
	@if [ ! -e ./bin ]; then mkdir ./bin; fi
	$(CC) $(CFLAGS) $(IPATH) -o src/tomsLogger.o -c src/tomsLogger.cpp
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o bin/tomsLogger src/tomsLogger.o $(CWLPATH) $(LPATH) $(LIBS)
