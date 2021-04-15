#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <util/MyString.h>
#include <Painter.h>

class Animation {
    public:
        Animation(const MyString& name) : _name(name) {};
        virtual void run(const Painter& painter, Cube& cube) = 0;
        const MyString& getName() const;

    protected:
        MyString _name;
};

#endif
