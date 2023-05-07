CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = client
OBJ1 = key
OBJ2 = keysystem
OBJ3 = user

all: clean ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ src/${OBJ0}.cpp src/${OBJ1}.cpp src/${OBJ2}.cpp src/${OBJ3}.cpp src/$@_functions.cpp
clean:
	rm -f ./${OBJ0}