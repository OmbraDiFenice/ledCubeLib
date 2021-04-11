#include <Animations.h>
#include <Painter.h>
#include <Cube.h>

#ifdef ARDUINO
    #include <stdlib.h>
#else
    #include <cstdlib>
    using std::rand;
#endif

void fixed(const Painter& painter, Cube& cube) {
    painter.paintCube(cube);
}

void scrollRows(const Painter& painter, Cube& cube) {
        for(unsigned int z = 0; z < cube.getSide(); ++z) {
            for(unsigned int y = 0; y < cube.getSide(); ++y) {
                for(unsigned int x = 0; x < cube.getSide(); ++x) {
                    cube.setPixel(x, y, z, true);
                    painter.paintCube(cube, 5);
                }
            }
        }
        for(int z = cube.getSide()-1; z >= 0; --z) {
            for(int y = cube.getSide()-1; y >= 0; --y) {
                for(int x = cube.getSide()-1; x >= 0; --x) {
                    cube.setPixel(x, y, z, false);
                    painter.paintCube(cube, 4);
                }
            }
        }
}

void scrollPlaneZ(const Painter& painter, Cube& cube) {
        for(unsigned int z = 0; z < cube.getSide(); ++z) {
            cube.setLayer(z, true);
            painter.paintCube(cube, 4);
            cube.setLayer(z, false);
        }
        for(unsigned int z = cube.getSide()-2; z > 0; --z) {
            cube.setLayer(z, true);
            painter.paintCube(cube, 4);
            cube.setLayer(z, false);
        }
}

void rain(const Painter& painter, Cube& cube) {
    static unsigned int counter = 0;

    cube.shiftLayers(-1);

    if((++counter) % 2 == 0) {    
        cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);
        cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);
        cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);
    }

    painter.paintCube(cube, 4);
}

