#include <Animations.h>
#include <Painter.h>
#include <Cube.h>

#ifdef ARDUINO
    #include <stdlib.h>
#else
    #include <cstdlib>
    using std::rand;
#endif

void Fixed::run(const Painter& painter, Cube& cube) {
    painter.paintCube(cube);
}
REGISTER(Fixed);

void ScrollRows::run(const Painter& painter, Cube& cube) {
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
REGISTER(ScrollRows);

void ScrollPlaneZ::run(const Painter& painter, Cube& cube) {
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
REGISTER(ScrollPlaneZ);

void Rain::run(const Painter& painter, Cube& cube) {
    cube.shiftLayers(-1);

    cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);
    cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);
    cube.setPixel(rand() % cube.getSide(), rand() % cube.getSide(), cube.getSide()-1, true);

    painter.paintCube(cube, 4);
}
REGISTER(Rain);

void RandomShift::run(const Painter& painter, Cube& cube) {
    unsigned int x = rand() % cube.getSide();
    unsigned int y = rand() % cube.getSide();

    if(cube.getPixel(x, y, 0)) {
        shiftUp(x, y, painter, cube);
    } else {
        shiftDown(x, y, painter, cube);
    }
    painter.paintCube(cube, 50);
}

void RandomShift::shiftUp(unsigned int x, unsigned int y, const Painter& painter, Cube& cube) {
    for(unsigned int z = 0; z < cube.getSide()-1; ++z) {
        cube.setPixel(x, y, z, false);
        cube.setPixel(x, y, z+1, true);
        painter.paintCube(cube);
    }
}

void RandomShift::shiftDown(unsigned int x, unsigned int y, const Painter& painter, Cube& cube) {
    for(unsigned int z = cube.getSide()-1; z > 0; --z) {
        cube.setPixel(x, y, z, false);
        cube.setPixel(x, y, z-1, true);
        painter.paintCube(cube);
    }
}
REGISTER(RandomShift);

void Snake::run(const Painter& painter, Cube& cube) {
    cube.setPixel(_snake[_tail].x, _snake[_tail].y, _snake[_tail].z, false);
    _tail = (_tail + 1) % _length;

    unsigned int currentHead = _head;
    _head = (_head + 1) % _length;
    _snake[_head] = findNext(cube, _snake[currentHead]);
    cube.setPixel(_snake[_head].x, _snake[_head].y, _snake[_head].z, true);

    painter.paintCube(cube, 5);
}

void Snake::init(Cube& cube) {
    _head = _length-1;
    _tail = 0;
    cube.clear();
    for(unsigned int i = 0; i < _length; ++i) {
        _snake[i].x = i;
    }
    cube.setPixel(_snake[_head].x, _snake[_head].y, _snake[_head].z, true);
};

Snake::Point Snake::findNext(Cube& cube, const Point& currentHead) const {
    Point next = currentHead;

    static int offset[] = { 1, -1 };
    int* point = (int*)(&next);

    while(!isValidNext(next, cube)) {
        next = currentHead;
        int coordinateIndex = rand() % 3;
        int offsetIndex = rand() % 2;
        point[coordinateIndex] += offset[offsetIndex];
    }

    return next;
}

bool Snake::isValidNext(const Snake::Point& candidateNext, const Cube& cube) const {
    return candidateNext.x >= 0 && candidateNext.x < cube.getSide()
        && candidateNext.y >= 0 && candidateNext.y < cube.getSide()
        && candidateNext.z >= 0 && candidateNext.z < cube.getSide()
        && !cube.getPixel(candidateNext.x, candidateNext.y, candidateNext.z);
}
REGISTER(Snake);
