#ifndef __ArduinoPainter_h__
#define __ArduinoPainter_h__

#include <Painter.h>

class ArduinoPainter : public Painter {
    public:
        ArduinoPainter(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin) : OUTPUT_READY_PIN(outputReadyPin), OUTPUT_PIN(outputPin), CLOCK_PIN(clockPin) {};

    protected:
        void initPaint() const override;
        void shiftOut(unsigned char data, ShiftMode shiftMode) const override;
        void dataReady() const override;
        void wait(int milliseconds) const override;

    private:
        const unsigned int OUTPUT_READY_PIN;
        const unsigned int OUTPUT_PIN;
        const unsigned int CLOCK_PIN;
};

#endif
