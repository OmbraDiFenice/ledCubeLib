LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -Isrc -g

all: raspi test

raspi: raspi.cpp src/Cube.o src/Painter.o src/Animator.o src/Animations.o src/pigpio/PigpioAnimator.o src/pigpio/PigpioPainter.o src/Animation.o src/util/MyString.o

test: CXXFLAGS+=-Itests
test: test.cpp tests/Testing.o src/Cube.o src/util/MyString.o tests/TestCube.o tests/util/TestMyString.o

tests/Testing.o: tests/Testing.h tests/Testing.cpp

src/util/MyString.o: src/util/MyString.h src/util/MyString.cpp

src/Animation.o: src/Animation.h src/Animation.cpp

Vector: src/Vector.h

.PHONY: clean
clean:
	rm src/*.o src/util/*.o src/pigpio/*.o raspi tests/util/*.o test
