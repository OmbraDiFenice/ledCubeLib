LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread

all: main

main: Painter.o Cube.o

Painter.o: Painter.cpp Painter.h

Cube.o: Cube.cpp Cube.h

.PHONY: clean
clean:
	rm *.o main
