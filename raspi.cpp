#include <Animator.h>
#include <Animations.h>
#include <Cube.h>
#include <Painter.h>
#include <pigpio/PigpioAnimator.h>

#define LED_READY_PIN 14
#define LED_OUT_PIN 15
#define CLOCK_PIN 18

int main(int argc, char** argv) {
    const Animator& animator = PigpioAnimator(LED_READY_PIN, LED_OUT_PIN, CLOCK_PIN);

    Cube cube(4);

    while(true) {
        animator.play(scrollPlanes, cube);
    }
}
