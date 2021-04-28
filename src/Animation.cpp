#include <Animation.h>

void Animation::init(Cube& cube) {
    cube.clear();
}

const MyString& Animation::getName() const {
    return _name;
}
