#ifndef __PigpioPainter_h__
#define __PigpioPainter_h__

#include <Painter.h>

class PigpioPainter : public Painter {
    public:
        PigpioPainter(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : OUTPUT_READY(outputReadyPin), OUTPUT(outputPin), CLOCK(clockPin) {};

    protected:
        void initPaint() const override;
        void shiftOut(unsigned char data, ShiftMode shiftMode) const override;
        void dataReady() const override;
        void wait(int milliseconds) const override;

    private:
        const unsigned int OUTPUT_READY;
        const unsigned int OUTPUT;
        const unsigned int CLOCK;
};

#endif
