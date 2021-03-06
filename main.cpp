#include <pigpio.h>
#include <iostream>
#include "Painter.h"

int main(int argc, char** argv) {
    int version = gpioInitialise();
    if(version == PI_INIT_FAILED) {
        std::cerr << "error initialising pigpio" << std::endl;
        return version;
    }

    std::cout << "hello world" << std::endl;

    const Painter& painter = PigpioPainter(1,2,3);

    gpioTerminate();
}
