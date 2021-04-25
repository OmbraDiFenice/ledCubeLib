#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <util/MyString.h>
#include <Painter.h>

class Animation {
    public:
        Animation(const MyString& name) : _name(name) {};
        virtual ~Animation() = default;
        virtual void run(const Painter& painter, Cube& cube) = 0;
        virtual void init(Cube& cube) {};
        const MyString& getName() const;

    protected:
        MyString _name;
};

#endif
