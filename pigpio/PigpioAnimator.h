#ifndef __PigpioAnimator_h__
#define __PigpioAnimator_h__

#include <Animator.h>
#include <pigpio/PigpioPainter.h>

#define CLOCK_PIN 18
#define LED_OUT_PIN 15
#define LED_READY_PIN 14

class PigpioAnimator : public Animator {
    public:
        PigpioAnimator();
        ~PigpioAnimator();

    protected:
        const Painter& getPainter() const override;

    private:
        PigpioPainter _painter;
};

#endif
