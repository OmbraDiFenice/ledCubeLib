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

void FixedOff::run(const Painter& painter, Cube& cube) {
    painter.paintCube(cube);
}
REGISTER(FixedOff);

void FixedOn::run(const Painter& painter, Cube& cube) {
    painter.paintCube(cube);
}
void FixedOn::init(Cube& cube) {
		for (unsigned int z = 0; z < cube.getSide(); ++z) {
				cube.setLayer(z, true);
		}
}
REGISTER(FixedOn);

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

Walls::Point& Walls::Point::operator+=(const Walls::Point& other) {
	x += other.x;
	y += other.y;

	return *this;
}

void Walls::run(const Painter& painter, Cube& cube) {
	bool shouldGrow = _currentLength < cube.getSide();

	for(unsigned int z = 0; z < cube.getSide(); ++z) {
		cube.setPixel(_head.x, _head.y, z, true);
		cube.setPixel(_tail.x, _tail.y, z, shouldGrow);
	}

	_lastHeadIncrement = findIncrement(_head, cube.getSide() - 1, _lastHeadIncrement);
	_head += _lastHeadIncrement;

	if(shouldGrow) {
		++_currentLength;
	} else {
		_lastTailIncrement = findIncrement(_tail, cube.getSide() - 1, _lastTailIncrement);
		_tail += _lastTailIncrement;
	}

	painter.paintCube(cube, 3);
}

void Walls::init(Cube& cube) {
	cube.clear();
	for(unsigned int z = 0; z < cube.getSide(); ++z) {
		cube.setPixel(0, 0, z, true);
	}

	_head = {1, 0};
	_tail = {0, 0};
	_lastHeadIncrement = {1, 0};
	_lastTailIncrement = {0, 0};
	_currentLength = 1;
}

Walls::Point Walls::findIncrement(const Walls::Point& head, unsigned int max, const Walls::Point& current) {
	Walls::Point increment = {0, 0};

	if(head.x == max && head.y == 0  ) { increment.y =  1; return increment; }
	if(head.x == max && head.y == max) { increment.x = -1; return increment; }
	if(head.x == 0   && head.y == max) { increment.y = -1; return increment; }
	if(head.x == 0   && head.y == 0  ) { increment.x =  1; return increment; }

	return current;
}
REGISTER(Walls);


RandomMultiShift::~RandomMultiShift() {
		if (z_cache != nullptr) delete[] z_cache;
		z_cache = nullptr;
		if (points != nullptr) delete[] points;
		points = nullptr;
}

void RandomMultiShift::init(Cube& cube) {
    cube.clear();
		if(z_cache == nullptr) z_cache = new unsigned int[cube.getSide() * cube.getSide()];
		if(points == nullptr) points = new PointShift[cube.getSide() * cube.getSide() / 2];

    for(unsigned int x = 0; x < cube.getSide(); ++x) {
				for(unsigned int y = 0; y < cube.getSide(); ++y) {
						unsigned int z = rand() % cube.getSide();
						cube.setPixel(x, y, z, true);
						z_cache[x * cube.getSide() + y] = z;
				}
    }
}

void RandomMultiShift::run(const Painter& painter, Cube& cube) {
		size_t count = rand() % (cube.getSide() * cube.getSide() / 2) + 1;
		unsigned int maxDistance = 0;

		for(size_t i = 0; i < count; ++i) {
				points[i].x = rand() % cube.getSide();
				points[i].y = rand() % cube.getSide();
				points[i].z = z_cache[points[i].x * cube.getSide() + points[i].y];

				unsigned int maxDistanceUp = cube.getSide() - 1 - points[i].z;
				unsigned int maxDistanceDown = points[i].z;

				points[i].slideUp = maxDistanceUp > maxDistanceDown;
				unsigned int distance = (rand() % (points[i].slideUp ? maxDistanceUp : maxDistanceDown)) + 1;
				points[i].distance = distance;

				if(distance > maxDistance) maxDistance = distance; 
		}

		while(maxDistance > 0) {
				slide(points, count, painter, cube);
				painter.paintCube(cube, 2);
				--maxDistance;
		}
    painter.paintCube(cube, 50);
}

void RandomMultiShift::slide(RandomMultiShift::PointShift* points, size_t count, const Painter& painter, Cube& cube) {
		for(size_t i = 0; i < count; ++i) {
				PointShift& point = points[i];
				if(point.distance <= 0) continue;

				cube.setPixel(point.x, point.y, point.z, false);
				point.z += point.slideUp ? 1 : -1;
				cube.setPixel(point.x, point.y, point.z, true);
				--point.distance;
				z_cache[point.x * cube.getSide() + point.y] = point.z;
		}
}
REGISTER(RandomMultiShift);

SubCubes::~SubCubes() {
		if (_subcube1 != nullptr) delete[] _subcube1;
		_subcube1 = nullptr;
		if (_subcube2 != nullptr) delete[] _subcube2;
		_subcube2 = nullptr;
}

void SubCubes::init(Cube& cube) {
		cube.clear();
		_subcubeSide = cube.getSide() / 2;
		_subcube1 = new Pixel3d[_subcubeSide * _subcubeSide * _subcubeSide];
		_subcube2 = new Pixel3d[_subcubeSide * _subcubeSide * _subcubeSide];
		_steps = cube.getSide() / 2;

		for(unsigned int x = 0; x < _subcubeSide; ++x) {
				for(unsigned int y = 0; y < _subcubeSide; ++y) {
						for (unsigned int z = 0; z < _subcubeSide; ++z) {
								_subcube1[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].x = x;
								_subcube1[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].y = y;
								_subcube1[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].z = z;

								_subcube2[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].x = cube.getSide() - 1 -x;
								_subcube2[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].y = cube.getSide() - 1 -y;
								_subcube2[x * _subcubeSide * _subcubeSide + y * _subcubeSide + z].z = cube.getSide() - 1 -z;
						}
				}
		}

		for(unsigned int i = 0; i < _subcubeSide * _subcubeSide * _subcubeSide; ++i) {
				cube.setPixel(_subcube1[i], true);
				cube.setPixel(_subcube2[i], true);
		}
}

void SubCubes::run(const Painter& painter, Cube& cube) {
		for(unsigned int i = 0; i < 6; ++i) {
				painter.paintCube(cube, 15);
				while(_steps > 0) {
						moveSubCube(_subcube1, _direction1[i], cube);
						moveSubCube(_subcube2, _direction2[i], cube);
						painter.paintCube(cube, 2);
						--_steps;
				}
				_steps = cube.getSide() / 2;
		}
}

void SubCubes::moveSubCube(Pixel3d* subcube, Vector3d vector, Cube& cube) {
		const unsigned int pixels = _subcubeSide * _subcubeSide * _subcubeSide;
		for(unsigned int i = 0; i < pixels; ++i) {
				cube.movePixel(subcube[i], vector);
		}
		for(unsigned int i = 0; i < pixels; ++i) {
				cube.setPixel(subcube[i], true);
		}
}
REGISTER(SubCubes);
