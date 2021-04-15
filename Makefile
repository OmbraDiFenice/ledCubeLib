CXXFLAGS=-Wall -pthread -Isrc -g

all: raspi test

raspi: LDLIBS+=-lpigpio
raspi: raspi.cpp src/Cube.o src/Painter.o src/Animator.o src/Animations.o src/pigpio/PigpioAnimator.o src/pigpio/PigpioPainter.o src/Animation.o src/util/MyString.o src/util/Vector.h

test: CXXFLAGS+=-Itests
test: test.cpp tests/Testing.o src/Cube.o src/util/MyString.o src/util/Vector.h tests/TestCube.o tests/util/TestMyString.o src/util/Vector.h tests/util/TestVector.o

tests/Testing.o: tests/Testing.h tests/Testing.cpp

tests/util/TestVector.o: tests/util/TestVector.h tests/util/TestVector.cpp src/util/Vector.h

src/util/MyString.o: src/util/MyString.h src/util/MyString.cpp

src/Animation.o: src/Animation.h src/Animation.cpp

.PHONY: clean
clean:
	rm src/*.o src/util/*.o src/pigpio/*.o raspi tests/util/*.o test
