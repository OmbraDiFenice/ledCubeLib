#ifndef __Cube_h__
#define __Cube_h__

class Cube {
    public:
        explicit Cube(unsigned int size);
        ~Cube();

        void clear();
        void setPixel(unsigned int x, unsigned int y, unsigned int z, bool value);
        void setLayer(unsigned int z, bool value);

        inline unsigned char* getBuffer() { return _layers; };

        inline const unsigned int getSide() const { return _side; };
        inline const unsigned int getSize() const { return _size; };
        inline const unsigned char* getLayer(unsigned int layer) const { return &_layers[layer * _bytesPerLayer]; };
        inline const unsigned int getBytesPerLayer() const { return _bytesPerLayer; };

    private:
        unsigned int _side;
        unsigned int _size;
        unsigned char* _layers;
        unsigned int _bytesPerLayer;
        unsigned int _linesPerByte;
};

#endif
