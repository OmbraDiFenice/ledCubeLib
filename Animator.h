#ifndef __Animator_h__
#define __Animator_h__

#include <Painter.h>

class Animator {
    public:
        Animator() = default;
        virtual ~Animator() = default;

        void play(void (*animation)(const Painter&, Cube&), Cube& cube) const;

    protected:
        virtual const Painter& getPainter() const = 0;
};

#endif
