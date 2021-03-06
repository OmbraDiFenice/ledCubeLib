LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread

all: main

main: Painter.o

.PHONY: clean
clean:
	rm *.o main
