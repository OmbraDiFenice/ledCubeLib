#include <pigpio/PigpioAnimator.h>

#include <pigpio.h>

PigpioAnimator::PigpioAnimator() : _painter(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN) {
    int version = gpioInitialise();
    if(version == PI_INIT_FAILED) {
        throw "error initialising pigpio";
    }

    gpioSetMode(LED_READY_PIN, PI_OUTPUT);
    gpioSetMode(LED_OUT_PIN, PI_OUTPUT);
    gpioSetMode(CLOCK_PIN, PI_OUTPUT);
}

PigpioAnimator::~PigpioAnimator() {
    gpioTerminate();
}

const Painter& PigpioAnimator::getPainter() const {
    return _painter;
}
