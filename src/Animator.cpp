#include <Animator.h>

void Animator::play(Animation& animation, Cube& cube) const {
    animation.run(getPainter(), cube);
}
