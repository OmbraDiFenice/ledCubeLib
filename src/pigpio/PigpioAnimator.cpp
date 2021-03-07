#ifndef ARDUINO

#include <pigpio/PigpioAnimator.h>

#include <pigpio.h>

PigpioAnimator::PigpioAnimator(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : _painter(outputReadyPin, outputPin, clockPin) {
    int version = gpioInitialise();
    if(version == PI_INIT_FAILED) {
        throw "error initialising pigpio";
    }

    gpioSetMode(outputReadyPin, PI_OUTPUT);
    gpioSetMode(outputPin, PI_OUTPUT);
    gpioSetMode(clockPin, PI_OUTPUT);
}

PigpioAnimator::~PigpioAnimator() {
    gpioTerminate();
}

const Painter& PigpioAnimator::getPainter() const {
    return _painter;
}

#endif
