LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -Isrc -g

all: raspi test

raspi: raspi.cpp src/Cube.o src/Painter.o src/Animator.o src/Animations.o src/pigpio/PigpioAnimator.o src/pigpio/PigpioPainter.o src/Animation.o src/MyString.o

test: test.cpp tests/Testing.o src/Cube.o src/MyString.o tests/TestCube.o tests/TestMyString.o

tests/Testing.o: tests/Testing.h tests/Testing.cpp

src/MyString.o: src/MyString.h src/MyString.cpp

src/Animation.o: src/Animation.h src/Animation.cpp

Vector: src/Vector.h

.PHONY: clean
clean:
	rm src/*.o src/pigpio/*.o raspi tests/*.o test
