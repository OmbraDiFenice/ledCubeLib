#ifndef __TESTCUBE_H__
#define __TESTCUBE_H__

#include <Testing.h>
#include <Cube.h>

class TestCube : public Test {
    public:
        TestCube() : cube(4) {};

    protected:
        bool isCleared(Cube& cube);
        void testSetPixel(unsigned int x, unsigned int y, unsigned int z, unsigned char *actual, unsigned char expected);

        Cube cube;
};

#endif
