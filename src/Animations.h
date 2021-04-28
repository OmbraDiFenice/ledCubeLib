#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include <Cube.h>
#include <Painter.h>
#include <Animation.h>
#include <AnimationRegistry.h>

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
        void init(Cube& cube) override;

    private:
        void shiftUp(unsigned int x, unsigned int y, const Painter& painter, Cube& cube);
        void shiftDown(unsigned int x, unsigned int y, const Painter& painter, Cube& cube);
};

class Snake : public Animation {
    public:
        Snake() : Animation("snake") {};
        void run(const Painter& painter, Cube& cube) override;
        void init(Cube& cube) override;

    private:
        struct Point { int x = 0, y = 0, z = 0; };

        Snake::Point findNext(Cube& cube, const Point& currentHead) const;
        bool isValidNext(const Snake::Point& candidateNext, const Cube& cube) const;

    private:
        static constexpr unsigned int _length = 4;
        Point _snake[_length];
        unsigned int _head;
        unsigned int _tail;
};

class Spin : public Animation {
    public:
        Spin() : Animation("spin") {};
        void run(const Painter& painter, Cube& cube) override;
        void init(Cube& cube) override;

    public:
        struct Point { unsigned int x; unsigned int y; };

    private:
        enum Direction { UP, DOWN };

    private:
        static constexpr unsigned int len = 8;
        static const Point position[len];
        unsigned int i;
        unsigned int z;
        Direction direction;
};

#endif
