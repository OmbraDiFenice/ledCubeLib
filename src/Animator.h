#ifndef __Animator_h__
#define __Animator_h__

#include <Painter.h>
#include <Animation.h>

class Animator {
    public:
        Animator() = default;
        virtual ~Animator() = default;

				void init(Cube& cube) const;
        void play(Animation& animation, Cube& cube) const;

    protected:
        virtual const Painter& getPainter() const = 0;
};

#endif
