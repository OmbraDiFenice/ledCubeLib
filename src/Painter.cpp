#include <Painter.h>

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
