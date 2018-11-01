# Author: Khomchenko Vladislav
# khomcvla@fit.cvut.cz

BINARY = ./khomcvla
DOC = doc
RM = rm -rf
SRC = src/vars.cpp src/main.cpp src/Ball.cpp src/Bonus.cpp src/Control.cpp src/Scores.cpp src/Load_SDL_GL.cpp src/Draw.cpp

CXX =g++
CXXFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb 
GL = -lGL -lGLU -lglut -lm
SDL = `sdl2-config --libs` -lSDL2_mixer


all: compile doc

# Delete binary and created documentation
clean:
	rm -r $(BINARY)
	rm -r $(DOC)

# Compile
compile: 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BINARY) $(SDL) $(GL)   

# Run the program
run:
	$(BINARY)

# Create documentation
doc: 
	doxygen

