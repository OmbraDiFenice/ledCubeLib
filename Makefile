LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread

all: main

main: Painter.o

Painter.o: Painter.cpp Painter.h

.PHONY: clean
clean:
	rm *.o main
