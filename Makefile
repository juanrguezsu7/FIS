CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = client
OBJ1 = key
OBJ2 = keysystem
OBJ3 = user

all: ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ ${OBJ0}.cpp ${OBJ1}.cpp ${OBJ2}.cpp ${OBJ3}.cpp $@_functions.cpp
clean:
	rm -f ./${OBJ0}