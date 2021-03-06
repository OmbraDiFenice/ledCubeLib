#include <pigpio.h>
#include <iostream>
#include "Painter.h"
#include "Cube.h"

#define CLOCK_PIN 18
#define LED_OUT_PIN 15
#define LED_READY_PIN 14

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

int main(int argc, char** argv) {
    int version = gpioInitialise();
    if(version == PI_INIT_FAILED) {
        std::cerr << "error initialising pigpio" << std::endl;
        return version;
    }

    gpioSetMode(LED_READY_PIN, PI_OUTPUT);
    gpioSetMode(LED_OUT_PIN, PI_OUTPUT);
    gpioSetMode(CLOCK_PIN, PI_OUTPUT);

    const Painter& painter = PigpioPainter(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);

    Cube cube(4);

    while(true) {
        scrollRows(painter, cube);
    }

    cube.clear();
    painter.paintCube(cube);

    gpioTerminate();
}
