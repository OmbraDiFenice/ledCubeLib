#ifndef __Painter_h__
#define __Painter_h__

#include "Cube.h"

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

class PigpioPainter : public Painter {
    public:
        PigpioPainter(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : OUTPUT_READY(outputReadyPin), OUTPUT(outputPin), CLOCK(clockPin) {};

    protected:
        void initPaint() const override;
        void shiftOut(unsigned char data, ShiftMode shiftMode) const override;
        void dataReady() const override;
        void wait(int milliseconds) const;


    private:
        const unsigned int OUTPUT_READY;
        const unsigned int OUTPUT;
        const unsigned int CLOCK;
};

#endif
