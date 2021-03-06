#include "Painter.h"

#include <pigpio.h>

unsigned char Painter::getMaskForBit(unsigned int bit) const {
    return 1 << bit;
}

void Painter::paintCube(unsigned int layer, unsigned char* layerData, unsigned int size) const {
    unsigned char layerByte = getMaskForBit(layer);

    initPaint();

    shiftOut(layerByte, ShiftMode::MSB_FIRST);
    shiftOut(0xFF, ShiftMode::LSB_FIRST);
    shiftOut(0xFF, ShiftMode::LSB_FIRST);

    dataReady();
}

void PigpioPainter::shiftOut(unsigned char data, ShiftMode shiftMode) const {
    gpioWrite(CLOCK, 0);

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
