#include "Cube.h"

#ifdef ARDUINO
	#include <string.h>
    #include <stdlib.h>
#else
	#include <cstring>
	#include <cstdlib>
	using std::memset;
	using std::memcpy;
    using std::abs;
#endif

Cube::Cube(unsigned int side) : _side(side) {
    _bytesPerLayer = (_side * _side) / 8;
    _linesPerByte = 8 / _side;
    _size = _side * _bytesPerLayer;
    _layers = new unsigned char[_size]; 
    clear();
};

Cube::Cube(const Cube& other) {
    _side = other._side;
    _bytesPerLayer = other._bytesPerLayer;
    _linesPerByte = other._linesPerByte;
    _size = other._size;
    _layers = new unsigned char[_size];
    memcpy(_layers, other._layers, _size);
}

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

void Cube::togglePixel(unsigned int x, unsigned int y, unsigned int z) {
    unsigned char* layer = &_layers[z * _bytesPerLayer];
    unsigned char mask = 1 << x;
    if(y % _linesPerByte == 0) mask <<= _side;
    bool isSet = (layer[y / _linesPerByte] & mask) != 0;
    if(!isSet) {
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

void Cube::shiftLayers(int amount) {
    if(amount == 0) return;
    unsigned int absAmount = abs(amount);
    if(absAmount >= _side) {
        clear();
        return;
    }

    Cube copy(*this);
    const unsigned char * source = amount < 0 ? copy.getLayer(absAmount) : copy.getLayer(0);
    unsigned char * destination  = amount < 0 ? findLayer(0)             : findLayer(absAmount);
    memcpy(destination, source, _bytesPerLayer * (_side - absAmount));

    unsigned char * clearFrom = amount < 0 ? findLayer(_side - absAmount) : findLayer(0);
    memset(clearFrom, 0, _bytesPerLayer * absAmount);
}

bool Cube::getPixel(unsigned int x, unsigned int y, unsigned int z) const {
    unsigned char* layer = &_layers[z * _bytesPerLayer];
    unsigned char mask = 1 << x;
    if(y % _linesPerByte == 0) mask <<= _side;
    return (layer[y / _linesPerByte] & mask) != 0;
}
