#include <AnimationRegistry.h>

#ifdef ARDUINO
    #include <stdio.h>
#else
    #include <cstdio>
#endif

AnimationRegistry& AnimationRegistry::GetInstance() {
    static AnimationRegistry instance;
    return instance;
}

Animation* AnimationRegistry::getById(unsigned int key) {
    if(key >= _animations.size()) return nullptr;
    return _animations.at(key);
} 

Animation* AnimationRegistry::getByName(const MyString& name) {
    for(unsigned int i = 0; i < _animations.size(); ++i) {
        Animation* anim = _animations.at(i);
        if(name == anim->getName()) {
            return anim;
        }
    }
    return nullptr;
}

MyString AnimationRegistry::toString() {
    MyString out;
    char* buf = new char[3];
    for(unsigned int i = 0; i < _animations.size(); ++i) {
        sprintf(buf, "%d", i);
        out.append(buf);
        out.append(" - ");
        out.append(_animations.at(i)->getName());
        out.append("\n");
    }
    return out;
}
