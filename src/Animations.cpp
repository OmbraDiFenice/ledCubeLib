#include <Animations.h>
#include <Painter.h>
#include <Cube.h>

#ifdef ARDUINO
    #include <stdlib.h>
    #include <math.h>
#else
    #include <cstdlib>
    #include <cmath>
    using std::rand;
	using std::memset;
    using std::pow;
#endif

void Fixed::run(const Painter& painter, Cube& cube) {
    painter.paintCube(cube);
}
REGISTER(Fixed);

void ScrollRows::run(const Painter& painter, Cube& cube) {
    int x = static_cast<unsigned int>(i / pow(cube.getSide(), 0)) % cube.getSide();
    int y = static_cast<unsigned int>(i / pow(cube.getSide(), 1)) % cube.getSide();
    int z = static_cast<unsigned int>(i / pow(cube.getSide(), 2)) % cube.getSide();

    cube.togglePixel(x, y, z);
    painter.paintCube(cube, 5);

    i = (i + 1) % static_cast<unsigned int>(pow(cube.getSide(), 3) + 1);
}

void ScrollRows::init(Cube& cube) {
    cube.clear();
    i = 0;
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

void RandomShift::init(Cube& cube) {
    cube.clear();
    cube.setLayer(0, true);
}

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
    return candidateNext.x >= 0 && candidateNext.x < static_cast<int>(cube.getSide())
        && candidateNext.y >= 0 && candidateNext.y < static_cast<int>(cube.getSide())
        && candidateNext.z >= 0 && candidateNext.z < static_cast<int>(cube.getSide())
        && !cube.getPixel(candidateNext.x, candidateNext.y, candidateNext.z);
}
REGISTER(Snake);

const Spin::Point Spin::position[] = {
    {1, 0}, {2, 0},
    {3, 1}, {3, 2},
    {2, 3}, {1, 3},
    {0, 2}, {0, 1}
};

void Spin::run(const Painter& painter, Cube& cube) {
    cube.setPixel(position[i].x, position[i].y, z, false);

    unsigned int deltaZ = (i + 1) / len;
    if(z == cube.getSide() - 1) direction = Direction::DOWN;
    if(z == 0) direction = Direction::UP;

    z += deltaZ * direction;

    i = (i + 1) % len;
    cube.setPixel(position[i].x, position[i].y, z, true);
    painter.paintCube(cube, 2);
}

void Spin::init(Cube& cube) {
    cube.clear();
    i = 0;
    z = 0;
    direction = Direction::UP;
}
REGISTER(Spin);

Waves::~Waves() {
    delete[] direction;
    direction = nullptr;
}

void Waves::run(const Painter& painter, Cube& cube) {
    unsigned int z;
    for(unsigned int x = 0; x < cube.getSide(); ++x) {
        z = findZ(x, cube);
        if(direction[x] != 0) {
            if(z == cube.getSide() - 1 || z == 0) {
                direction[x] = 0;
            }
        }
        else {
            if(z == cube.getSide() - 1) {
                direction[x] = -1;
            } else if(z == 0) {
                direction[x] = 1;
            }
        }
        moveLine(x, z, z + direction[x], cube);
    }
    painter.paintCube(cube, 5);
}

unsigned int Waves::findZ(unsigned int x, Cube& cube) const {
    for(unsigned int z = 0; z < cube.getSide(); ++z) {
        if(cube.getPixel(x, 0, z)) return z;
    }
    return 0;
}

void Waves::moveLine(unsigned int x, unsigned int currentZ, unsigned int newZ, Cube& cube) {
    for(unsigned int y = 0; y < cube.getSide(); ++y) {
        cube.setPixel(x, y, currentZ, false);
        cube.setPixel(x, y, newZ, true);
    }
}

void Waves::init(Cube& cube) {
    cube.clear();
    if(direction == nullptr) direction = new int[cube.getSide()];
    for(unsigned int x = 0; x < cube.getSide(); ++x) {
        direction[x] = 1;
        for(unsigned int y = 0; y < cube.getSide(); ++y) {
            cube.setPixel(x, y, x, true);
        }
    }
}
REGISTER(Waves);
