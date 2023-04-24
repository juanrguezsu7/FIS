CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = client
OBJ1 = key
OBJ2 = keysystem

all: ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ ${OBJ0}.cpp ${OBJ1}.cpp ${OBJ2}.cpp
clean:
	rm -f ./${OBJ0}