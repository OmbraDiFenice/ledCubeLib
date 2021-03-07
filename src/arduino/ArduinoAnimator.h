#ifndef __ArduinoAnimator_h__
#define __ArduinoAnimator_h__

#include <Animator.h>
#include "ArduinoPainter.h"

class ArduinoAnimator : public Animator {
    public:
        ArduinoAnimator(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin);
        ~ArduinoAnimator() = default;

    protected:
        const Painter& getPainter() const override;

    private:
        ArduinoPainter _painter;
};

#endif
