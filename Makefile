LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -Isrc -g

all: raspi test

raspi: raspi.cpp src/Cube.o src/Painter.o src/Animator.o src/Animations.o src/pigpio/PigpioAnimator.o src/pigpio/PigpioPainter.o

test: test.cpp tests/Testing.o src/Cube.o tests/TestCube.o

tests/Testing.o: tests/Testing.h tests/Testing.cpp

.PHONY: clean
clean:
	rm src/*.o src/pigpio/*.o raspi tests/*.o test
