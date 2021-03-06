#include "Painter.h"

#include <pigpio.h>

unsigned char Painter::getMaskForBit(unsigned int bit) const {
    return 1 << bit;
}

unsigned char Painter::getNthBit(unsigned char byte, unsigned int n) const {
    return (byte & getMaskForBit(n)) >> n;
}

void Painter::paintCube(const Cube& cube, unsigned int frames) const {
    initPaint();

    const unsigned char* plane;

    for(unsigned int frame = 0; frame < frames; ++frame) {
        for(unsigned int z = 0; z < cube.getSize(); ++z) {
            plane = cube.getLayer(z);
            
            // layer selection
            shiftOut(getMaskForBit(z), ShiftMode::MSB_FIRST);

            // draw xy plane
            for(unsigned int i = 0; i < cube.getBytesPerLayer(); ++i) {
                shiftOut(plane[i], ShiftMode::MSB_FIRST);
            }

            dataReady();
            wait(4);
        }
    }
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

void PigpioPainter::wait(int milliseconds) const {
    gpioSleep(PI_TIME_RELATIVE, 0, milliseconds * 1000);
}
