#include "Painter.h"

#include <pigpio.h>

unsigned char Painter::setBit(unsigned int bit) const {
    return 1 << bit;
}

void Painter::paintCube(unsigned int layer, unsigned char* layerData, unsigned int size) const {
    unsigned char layerByte = setBit(layer);

    initPaint();

    shiftOut(layerByte);
    shiftOut(0xFF);
    shiftOut(0xFF);

    dataReady();
}

void PigpioPainter::shiftOut(unsigned char data) const {
    gpioWrite(CLOCK, 0);

    for(int i = 0; i < 8; ++i) {
        // LSB first
        unsigned int bit = (data >> i) & 0x01;

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
}
