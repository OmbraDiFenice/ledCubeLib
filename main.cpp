#include <pigpio.h>
#include <iostream>
#include "Painter.h"

#define CLOCK_PIN 18
#define LED_OUT_PIN 15
#define LED_READY_PIN 14

#define SIZE_X 4
#define SIZE_Y 4
#define SIZE_Z 4

int main(int argc, char** argv) {
    int version = gpioInitialise();
    if(version == PI_INIT_FAILED) {
        std::cerr << "error initialising pigpio" << std::endl;
        return version;
    }

    gpioSetMode(LED_READY_PIN, PI_OUTPUT);
    gpioSetMode(LED_OUT_PIN, PI_OUTPUT);
    gpioSetMode(CLOCK_PIN, PI_OUTPUT);

    const Painter& painter = PigpioPainter(SIZE_X, SIZE_Y, SIZE_Z, LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);

    unsigned char cubeBuffer[SIZE_X][SIZE_Y][SIZE_Z];
    

    painter.paintCube(0, nullptr, 0);

    gpioTerminate();
}
