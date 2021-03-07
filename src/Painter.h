#ifndef __Painter_h__
#define __Painter_h__

#include <Cube.h>

class Painter {
    public:
        enum ShiftMode {
            LSB_FIRST,
            MSB_FIRST
        };

        virtual ~Painter() = default;

        void paintCube(const Cube& cube, unsigned int frames = 1) const;

    protected:
        virtual void initPaint() const = 0;
        virtual void shiftOut(unsigned char data, ShiftMode shiftMode) const = 0;
        virtual void dataReady() const = 0;
        virtual void wait(int milliseconds) const = 0;

        unsigned char getMaskForBit(unsigned int bit) const;
        unsigned char getNthBit(unsigned char byte, unsigned int n) const;
};

#endif
