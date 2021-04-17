#ifndef __TESTANIMATIONREGISTRY_H__
#define __TESTANIMATIONREGISTRY_H__

#include <Testing.h>
#include <AnimationRegistry.h>
#include <Animation.h>

class TestAnimation1 : public Animation {
    public:
        TestAnimation1() : Animation("TestAnimation1") {};
        void run(const Painter& painter, Cube& cube) {};
};

class TestAnimation2 : public Animation {
    public:
        TestAnimation2() : Animation("TestAnimation2") {};
        void run(const Painter& painter, Cube& cube) {};
};

class TestAnimationRegistry : public Test {
    protected:
        AnimationRegistry registry;
};

#endif
