#include "Testing.h"
#include "Cube.h"

void testCube() {
    Cube cube(4);

    ASSERT(cube.getSide() == 4, "wrong side");
}
