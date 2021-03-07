#include <Cube.h>
#include <Painter.h>
#include <Animator.h>
#include <pigpio/PigpioAnimator.h>

#define LED_READY_PIN 14
#define LED_OUT_PIN 15
#define CLOCK_PIN 18

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
    const Animator& animator = PigpioAnimator(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);

    Cube cube(4);

    while(true) {
        animator.play(scrollPlanes, cube);
    }
}
