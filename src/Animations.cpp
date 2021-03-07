#include <Animations.h>
#include <Painter.h>
#include <Cube.h>

void scrollRows(const Painter& painter, Cube& cube) {
        for(unsigned int z = 0; z < 4; ++z) { 
            for(unsigned int y = 0; y < 4; ++y) { 
                for(unsigned int x = 0; x < 4; ++x) { 
                    cube.setPixel(x, y, z, true);
                    painter.paintCube(cube, 50);
                }
            }
        }
        cube.clear();
        painter.paintCube(cube);
}

void scrollPlanes(const Painter& painter, Cube& cube) {
        for(unsigned int z = 0; z < 4; ++z) {
            cube.setLayer(z, true);
            painter.paintCube(cube, 150);
            cube.setLayer(z, false);
        }
        cube.clear();
        painter.paintCube(cube);
}

