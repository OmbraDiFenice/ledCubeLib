#ifndef ARDUINO
#ifndef __PigpioAnimator_h__
#define __PigpioAnimator_h__

#include <Animator.h>
#include <pigpio/PigpioPainter.h>

class PigpioAnimator : public Animator {
    public:
        PigpioAnimator(unsigned int outputReadyPin, unsigned int outputPin, unsigned int clockPin);
        ~PigpioAnimator();

    protected:
        const Painter& getPainter() const override;

    private:
        PigpioPainter _painter;
};

#endif
#endif
