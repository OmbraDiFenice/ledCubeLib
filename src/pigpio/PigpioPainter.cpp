#ifndef ARDUINO

#include <pigpio/PigpioPainter.h>

#include <pigpio.h>

void PigpioPainter::shiftOut(unsigned char data, ShiftMode shiftMode) const {
    for(int i = 0; i < 8; ++i) {
        unsigned int bit = (data >> (shiftMode == ShiftMode::LSB_FIRST ? i : (7 - i))) & 0x01;

        gpioWrite(OUTPUT, bit);
        gpioWrite(CLOCK, 1);
        gpioWrite(CLOCK, 0);
    }
}

void PigpioPainter::dataReady() const {
    gpioWrite(OUTPUT_READY, 1);
    gpioWrite(OUTPUT_READY, 0);
}

void PigpioPainter::initPaint() const {
    gpioWrite(OUTPUT_READY, 0);
    gpioWrite(CLOCK, 0);
}

void PigpioPainter::wait(int milliseconds) const {
    gpioSleep(PI_TIME_RELATIVE, 0, milliseconds * 1000);
}

#endif
