LDLIBS=-lpigpio
CXXFLAGS=-Wall -pthread -I.

all: raspi

raspi: raspi.cpp Cube.o Painter.o Animator.o Animations.o pigpio/PigpioAnimator.o pigpio/PigpioPainter.o

.PHONY: clean
clean:
	rm *.o pigpio/*.o raspi
