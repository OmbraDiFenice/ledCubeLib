#include <Animator.h>

void Animator::play(void (*animation)(const Painter&, Cube&), Cube& cube) const {
    animation(getPainter(), cube);
}
