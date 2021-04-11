#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include <Cube.h>
#include <Painter.h>
#include <Animation.h>

class Fixed : public Animation {
    public:
        Fixed() : Animation("fixed") {};
        void run(const Painter& painter, Cube& cube) override;
};

class ScrollRows : public Animation {
    public:
        ScrollRows() : Animation("scrollRows") {};
        void run(const Painter& painter, Cube& cube) override;
};

class ScrollPlaneZ : public Animation {
    public:
        ScrollPlaneZ() : Animation("scrollPlaneZ") {};
        void run(const Painter& painter, Cube& cube) override;
};

class Rain : public Animation {
    public:
        Rain() : Animation("rain") {};
        void run(const Painter& painter, Cube& cube) override;
};

class RandomShift : public Animation {
    public:
        RandomShift() : Animation("randomShift") {};
        void run(const Painter& painter, Cube& cube) override;

    private:
        void shiftUp(unsigned int x, unsigned int y, const Painter& painter, Cube& cube);
        void shiftDown(unsigned int x, unsigned int y, const Painter& painter, Cube& cube);
};

#endif
