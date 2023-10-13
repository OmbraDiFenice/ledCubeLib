#include <Animator.h>

void Animator::play(Animation& animation, Cube& cube) const {
    animation.run(getPainter(), cube);
}

void Animator::init(Cube& cube) const {
	cube.clear();
	getPainter().paintCube(cube);
}
