LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -Isrc

all: raspi test

raspi: raspi.cpp src/Cube.o src/Painter.o src/Animator.o src/Animations.o src/pigpio/PigpioAnimator.o src/pigpio/PigpioPainter.o

test: test.cpp tests/Testing.h tests/Testing.o src/Cube.o tests/TestCube.o

.PHONY: clean
clean:
	rm src/*.o src/pigpio/*.o raspi tests/*.o test
