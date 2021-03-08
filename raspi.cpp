#include <Cube.h>
#include <pigpio.h>
#include <iostream>

int main(int argc, char** argv) {
    if(gpioInitialise() < 0) return 1;

    Cube cube(4);
    int serialHandler = serOpen(argv[1], 9600, 0);

    for(unsigned int z = 0; z < 4; ++z) { 
        for(unsigned int y = 0; y < 4; ++y) { 
            for(unsigned int x = 0; x < 4; ++x) { 
                cube.setPixel(x, y, z, true);
                serWrite(serialHandler, reinterpret_cast<char*>(cube.getBuffer()), cube.getSize());
                getchar();
            }
        }
    }

    return 0;
}
