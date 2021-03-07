LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -I.

all: main

main: Cube.o Painter.o Animator.o pigpio/PigpioAnimator.o pigpio/PigpioPainter.o

pigpio/PigpioPainter.o: Painter.o pigpio/PigpioPainter.cpp pigpio/PigpioPainter.h

pigpio/PigpioAnimator.o: Animator.o pigpio/PigpioAnimator.cpp pigpio/PigpioAnimator.h

Painter.o: Painter.cpp Painter.h

Animator.o: Animator.cpp Animator.h

Cube.o: Cube.cpp Cube.h

.PHONY: clean
clean:
	rm *.o main
