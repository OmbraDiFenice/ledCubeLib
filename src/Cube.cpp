#include "Cube.h"

#ifdef ARDUINO
	#include "string.h"
#else
	#include <cstring>
	using std::memset;
#endif

Cube::Cube(unsigned int side) : _side(side) {
    _bytesPerLayer = (_side * _side) / 8;
    _linesPerByte = 8 / _side;
    _size = _side * _bytesPerLayer;
    _layers = new unsigned char[_size]; 
    clear();
};

Cube::~Cube() {
    delete[] _layers;
}

void Cube::clear() {
    memset(_layers, 0, _size);
}

void Cube::setPixel(unsigned int x, unsigned int y, unsigned int z, bool value) {
    unsigned char* layer = &_layers[z * _bytesPerLayer];
    unsigned char mask = 1 << x;
    if(y % _linesPerByte == 0) mask <<= _side;
    if(value) {
        layer[y / _linesPerByte] |= mask;
    } else {
        layer[y / _linesPerByte] &= ~(mask);
    }
}

void Cube::setLayer(unsigned int z, bool value) {
    unsigned char* layer = &_layers[z * _bytesPerLayer];
    for(unsigned int i = 0; i < _bytesPerLayer; ++i) {
        layer[i] = value ? 0xFF : 0x00;
    }
}
