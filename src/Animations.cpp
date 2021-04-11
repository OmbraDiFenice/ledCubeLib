#include <Animations.h>
#include <Painter.h>
#include <Cube.h>

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

