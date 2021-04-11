#include "Testing.h"
#include "Cube.h"

#ifdef ARDUINO
    #include <stdlib.h>
    #include <string.h>
#else
    #include <cstdio>
    #include <cstring>
	using std::memcpy;
#endif

class TestCube : public Test {
    public:
        TestCube() : cube(4) {};

    protected:
        bool isCleared(Cube& cube);
        void testSetPixel(unsigned int x, unsigned int y, unsigned int z, unsigned char *actual, unsigned char expected);

        Cube cube;
};

bool TestCube::isCleared(Cube& cube) {
    unsigned char * buf = cube.getBuffer();
    for(unsigned int i = 0; i < cube.getSize(); ++i) {
        if(buf[i] != 0) return false;
    }
    return true;
}

void TestCube::testSetPixel(unsigned int x, unsigned int y, unsigned int z, unsigned char *actual, unsigned char expected) {
    char errMsg[100];
    cube.setPixel(x, y, z, true);
    sprintf(errMsg, "error on x = %d, y = %d, z = %d - got %02X, expected: %02X", x, y, z, *actual, expected);
    ASSERT(*actual == expected, errMsg);
    cube.setPixel(x, y, z, false);
}

TEST(TestCube, copy) {
    Cube other(cube);

    ASSERT(other.getSize() == cube.getSize(), "sizes should match");
    ASSERT(other.getSide() == cube.getSide(), "sides should match");
    for(unsigned int i = 0; i < cube.getSize(); ++i) {
        ASSERT(other.getBuffer()[i] == cube.getBuffer()[i], "copy should be equal to original");
    }
}

TEST(TestCube, getSide) {
    ASSERT(cube.getSide() == 4, "wrong side");
}

TEST(TestCube, getSize) {
    ASSERT(cube.getSize() == 8, "wrong size");
}

TEST(TestCube, getBytesPerLayer) {
    ASSERT(cube.getBytesPerLayer() == 2, "wrong bytes per layer");
}

TEST(TestCube, startCleared) {
    ASSERT(isCleared(cube), "start cleared");
}

TEST(TestCube, setLayer0) {
    unsigned char * buf = cube.getBuffer();
    cube.setLayer(0, true);
    ASSERT(buf[0] == 0xff && buf[1] == 0xff
        && buf[2] == 0x00 && buf[3] == 0x00
        && buf[4] == 0x00 && buf[5] == 0x00
        && buf[6] == 0x00 && buf[7] == 0x00,
            "layer 0 only set");
}

TEST(TestCube, setLayer1) {
    unsigned char * buf = cube.getBuffer();
    cube.setLayer(1, true);
    ASSERT(buf[0] == 0x00 && buf[1] == 0x00
        && buf[2] == 0xff && buf[3] == 0xff
        && buf[4] == 0x00 && buf[5] == 0x00
        && buf[6] == 0x00 && buf[7] == 0x00,
            "layer 1 only set");
}

TEST(TestCube, setLayer2) {
    unsigned char * buf = cube.getBuffer();
    cube.setLayer(2, true);
    ASSERT(buf[0] == 0x00 && buf[1] == 0x00
        && buf[2] == 0x00 && buf[3] == 0x00
        && buf[4] == 0xff && buf[5] == 0xff
        && buf[6] == 0x00 && buf[7] == 0x00,
            "layer 2 only set");
}

TEST(TestCube, setLayer3) {
    unsigned char * buf = cube.getBuffer();
    cube.setLayer(3, true);
    ASSERT(buf[0] == 0x00 && buf[1] == 0x00
        && buf[2] == 0x00 && buf[3] == 0x00
        && buf[4] == 0x00 && buf[5] == 0x00
        && buf[6] == 0xff && buf[7] == 0xff,
            "layer 3 only set");
}

TEST(TestCube, getLayer0) {
    unsigned char * buf = cube.getBuffer();
    buf[0] = 0xAA;
    buf[1] = 0xBB;
    
    const unsigned char * layer = cube.getLayer(0);
    ASSERT(layer[0] == 0xAA && layer[1] == 0xBB, "layer 0 pattern");
}

TEST(TestCube, getLayer1) {
    unsigned char * buf = cube.getBuffer();
    buf[2] = 0xAA;
    buf[3] = 0xBB;
    
    const unsigned char * layer = cube.getLayer(1);
    ASSERT(layer[0] == 0xAA && layer[1] == 0xBB, "layer 1 pattern");
}

TEST(TestCube, getLayer2) {
    unsigned char * buf = cube.getBuffer();
    buf[4] = 0xAA;
    buf[5] = 0xBB;
    
    const unsigned char * layer = cube.getLayer(2);
    ASSERT(layer[0] == 0xAA && layer[1] == 0xBB, "layer 2 pattern");
}

TEST(TestCube, getLayer3) {
    unsigned char * buf = cube.getBuffer();
    buf[6] = 0xAA;
    buf[7] = 0xBB;
    
    const unsigned char * layer = cube.getLayer(3);
    ASSERT(layer[0] == 0xAA && layer[1] == 0xBB, "layer 3 pattern");
}

TEST(TestCube, clear) {
    unsigned char * buf = cube.getBuffer();
    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04;
    buf[4] = 0x05;
    buf[5] = 0x06;
    buf[6] = 0x07;
    buf[7] = 0x08;

    ASSERT(isCleared(cube) == false, "failed to dirty cube data");

    cube.clear();

    ASSERT(isCleared(cube) == true, "cube should be cleared");
}

TEST(TestCube, setPixel) {
    ASSERT(isCleared(cube) == true, "this test requires the cube to start cleared");

    unsigned char * buf = cube.getBuffer();

    // layer 0
    testSetPixel(0, 0, 0, &buf[0], 0b00010000);
    testSetPixel(1, 0, 0, &buf[0], 0b00100000);
    testSetPixel(2, 0, 0, &buf[0], 0b01000000);
    testSetPixel(3, 0, 0, &buf[0], 0b10000000);

    testSetPixel(0, 1, 0, &buf[0], 0b00000001);
    testSetPixel(1, 1, 0, &buf[0], 0b00000010);
    testSetPixel(2, 1, 0, &buf[0], 0b00000100);
    testSetPixel(3, 1, 0, &buf[0], 0b00001000);

    testSetPixel(0, 2, 0, &buf[1], 0b00010000);
    testSetPixel(1, 2, 0, &buf[1], 0b00100000);
    testSetPixel(2, 2, 0, &buf[1], 0b01000000);
    testSetPixel(3, 2, 0, &buf[1], 0b10000000);

    testSetPixel(0, 3, 0, &buf[1], 0b00000001);
    testSetPixel(1, 3, 0, &buf[1], 0b00000010);
    testSetPixel(2, 3, 0, &buf[1], 0b00000100);
    testSetPixel(3, 3, 0, &buf[1], 0b00001000);
    
    // layer 1
    testSetPixel(0, 0, 1, &buf[2], 0b00010000);
    testSetPixel(1, 0, 1, &buf[2], 0b00100000);
    testSetPixel(2, 0, 1, &buf[2], 0b01000000);
    testSetPixel(3, 0, 1, &buf[2], 0b10000000);

    testSetPixel(0, 1, 1, &buf[2], 0b00000001);
    testSetPixel(1, 1, 1, &buf[2], 0b00000010);
    testSetPixel(2, 1, 1, &buf[2], 0b00000100);
    testSetPixel(3, 1, 1, &buf[2], 0b00001000);

    testSetPixel(0, 2, 1, &buf[3], 0b00010000);
    testSetPixel(1, 2, 1, &buf[3], 0b00100000);
    testSetPixel(2, 2, 1, &buf[3], 0b01000000);
    testSetPixel(3, 2, 1, &buf[3], 0b10000000);

    testSetPixel(0, 3, 1, &buf[3], 0b00000001);
    testSetPixel(1, 3, 1, &buf[3], 0b00000010);
    testSetPixel(2, 3, 1, &buf[3], 0b00000100);
    testSetPixel(3, 3, 1, &buf[3], 0b00001000);
    
    // layer 2
    testSetPixel(0, 0, 2, &buf[4], 0b00010000);
    testSetPixel(1, 0, 2, &buf[4], 0b00100000);
    testSetPixel(2, 0, 2, &buf[4], 0b01000000);
    testSetPixel(3, 0, 2, &buf[4], 0b10000000);

    testSetPixel(0, 1, 2, &buf[4], 0b00000001);
    testSetPixel(1, 1, 2, &buf[4], 0b00000010);
    testSetPixel(2, 1, 2, &buf[4], 0b00000100);
    testSetPixel(3, 1, 2, &buf[4], 0b00001000);

    testSetPixel(0, 2, 2, &buf[5], 0b00010000);
    testSetPixel(1, 2, 2, &buf[5], 0b00100000);
    testSetPixel(2, 2, 2, &buf[5], 0b01000000);
    testSetPixel(3, 2, 2, &buf[5], 0b10000000);

    testSetPixel(0, 3, 2, &buf[5], 0b00000001);
    testSetPixel(1, 3, 2, &buf[5], 0b00000010);
    testSetPixel(2, 3, 2, &buf[5], 0b00000100);
    testSetPixel(3, 3, 2, &buf[5], 0b00001000);
    
    // layer 3
    testSetPixel(0, 0, 3, &buf[6], 0b00010000);
    testSetPixel(1, 0, 3, &buf[6], 0b00100000);
    testSetPixel(2, 0, 3, &buf[6], 0b01000000);
    testSetPixel(3, 0, 3, &buf[6], 0b10000000);

    testSetPixel(0, 1, 3, &buf[6], 0b00000001);
    testSetPixel(1, 1, 3, &buf[6], 0b00000010);
    testSetPixel(2, 1, 3, &buf[6], 0b00000100);
    testSetPixel(3, 1, 3, &buf[6], 0b00001000);

    testSetPixel(0, 2, 3, &buf[7], 0b00010000);
    testSetPixel(1, 2, 3, &buf[7], 0b00100000);
    testSetPixel(2, 2, 3, &buf[7], 0b01000000);
    testSetPixel(3, 2, 3, &buf[7], 0b10000000);

    testSetPixel(0, 3, 3, &buf[7], 0b00000001);
    testSetPixel(1, 3, 3, &buf[7], 0b00000010);
    testSetPixel(2, 3, 3, &buf[7], 0b00000100);
    testSetPixel(3, 3, 3, &buf[7], 0b00001000);
}

TEST(TestCube, shiftLayers_input0) {
    unsigned char copy[cube.getSize()];
    cube.setLayer(1, true);
    memcpy(copy, cube.getBuffer(), cube.getSize());

    for(unsigned int i = 0; i < cube.getSize(); ++i) {
        ASSERT(cube.getBuffer()[i] == copy[i], "cube should not change");
    }
}

TEST(TestCube, shiftLayers_down_equalSide) {
    cube.setLayer(cube.getSide()-1, true);
    cube.shiftLayers(-4);

    ASSERT(isCleared(cube), "cube should be cleared");
}

TEST(TestCube, shiftLayers_down_moreThanSide) {
    cube.setLayer(cube.getSide()-1, true);
    cube.shiftLayers(-10);

    ASSERT(isCleared(cube), "cube should be cleared");
}

TEST(TestCube, shiftLayers_down1) {
    cube.setLayer(cube.getSide()-1, true);
    cube.shiftLayers(-1);

    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[1], "original layer not emptied");

    ASSERT(0xFF == cube.getLayer(cube.getSide()-2)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(cube.getSide()-2)[1], "destination layer not set");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-3)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-3)[1], "other layer not empty");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-4)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-4)[1], "other layer not empty");
}

TEST(TestCube, shiftLayers_down2) {
    cube.setLayer(cube.getSide()-1, true);
    cube.shiftLayers(-2);

    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[1], "original layer not emptied");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-2)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-2)[1], "other layer not empty");

    ASSERT(0xFF == cube.getLayer(cube.getSide()-3)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(cube.getSide()-3)[1], "destination layer not set");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-4)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-4)[1], "other layer not empty");
}

TEST(TestCube, shiftLayers_down3) {
    cube.setLayer(cube.getSide()-1, true);
    cube.shiftLayers(-3);

    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-1)[1], "original layer not emptied");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-2)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-2)[1], "other layer not empty");

    ASSERT(0x00 == cube.getLayer(cube.getSide()-3)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(cube.getSide()-3)[1], "other layer not empty");

    ASSERT(0xFF == cube.getLayer(cube.getSide()-4)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(cube.getSide()-4)[1], "destination layer not set");
}

TEST(TestCube, shiftLayers_up_equalSide) {
    cube.setLayer(0, true);
    cube.shiftLayers(4);

    ASSERT(isCleared(cube), "cube should be cleared");
}

TEST(TestCube, shiftLayers_up_moreThanSide) {
    cube.setLayer(0, true);
    cube.shiftLayers(10);

    ASSERT(isCleared(cube), "cube should be cleared");
}

TEST(TestCube, shiftLayers_up1) {
    cube.setLayer(0, true);
    cube.shiftLayers(1);

    ASSERT(0x00 == cube.getLayer(0)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(0)[1], "original layer not emptied");

    ASSERT(0xFF == cube.getLayer(1)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(1)[1], "destination layer not set");

    ASSERT(0x00 == cube.getLayer(2)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(2)[1], "other layer not empty");

    ASSERT(0x00 == cube.getLayer(3)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(3)[1], "other layer not empty");
}

TEST(TestCube, shiftLayers_up2) {
    cube.setLayer(0, true);
    cube.shiftLayers(2);

    ASSERT(0x00 == cube.getLayer(0)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(0)[1], "original layer not emptied");

    ASSERT(0x00 == cube.getLayer(1)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(1)[1], "other layer not empty");

    ASSERT(0xFF == cube.getLayer(2)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(2)[1], "destination layer not set");

    ASSERT(0x00 == cube.getLayer(3)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(3)[1], "other layer not empty");
}

TEST(TestCube, shiftLayers_up3) {
    cube.setLayer(0, true);
    cube.shiftLayers(3);

    ASSERT(0x00 == cube.getLayer(0)[0], "original layer not emptied");
    ASSERT(0x00 == cube.getLayer(0)[1], "original layer not emptied");

    ASSERT(0x00 == cube.getLayer(1)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(1)[1], "other layer not empty");

    ASSERT(0x00 == cube.getLayer(2)[0], "other layer not empty");
    ASSERT(0x00 == cube.getLayer(2)[1], "other layer not empty");

    ASSERT(0xFF == cube.getLayer(3)[0], "destination layer not set");
    ASSERT(0xFF == cube.getLayer(3)[1], "destination layer not set");
}

void testCube() {
    TestCube suite;
    suite.run();
}
