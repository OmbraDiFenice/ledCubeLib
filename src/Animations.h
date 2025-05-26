#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include <Cube.h>
#include <Painter.h>
#include <Animation.h>
#include <AnimationRegistry.h>

class FixedOff : public Animation {
    public:
        FixedOff() : Animation("fixed off") {};
        void run(const Painter& painter, Cube& cube) override;
};

class FixedOn: public Animation {
		public:
				FixedOn() : Animation("fixed on") {};
				void run(const Painter& painter, Cube& cube) override;
				void init(Cube& cube) override;
};

class ScrollRows : public Animation {
    public:
        ScrollRows() : Animation("scrollRows") {};
        void run(const Painter& painter, Cube& cube) override;
        void init(Cube& cube) override;

    private:
        int i;
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
        enum Direction { UP = 1, DOWN = -1 };

    private:
        static constexpr unsigned int len = 8;
        static const Point position[len];
        unsigned int i;
        unsigned int z;
        Direction direction;
};

class Waves : public Animation {
    public:
        Waves() : Animation("waves"), direction(nullptr) {};
        virtual ~Waves();
        void run(const Painter& painter, Cube& cube) override;
        void init(Cube& cube) override;

    private:
        unsigned int findZ(unsigned int x, Cube& cube) const;
        void moveLine(unsigned int x, unsigned int currentZ, unsigned int newZ, Cube& cube);

    private:
        int *direction;
};

class Walls : public Animation {
    public:
        Walls() : Animation("walls") {};
        void run(const Painter& painter, Cube& cube) override;
        void init(Cube& cube) override;

		public:
				struct Point{ unsigned int x; unsigned int y; Walls::Point& operator+=(const Walls::Point& other); };

		private:
				Walls::Point findIncrement(const Walls::Point& head, unsigned int max, const Walls::Point& current);

		private:
				Point _head;
				Point _tail;
				Point _lastHeadIncrement;
				Point _lastTailIncrement;
				unsigned int _currentLength;
};

class RandomMultiShift : public Animation {
		public:
				RandomMultiShift() : Animation("random multi shift") {};
				virtual ~RandomMultiShift();
				void init(Cube& cube) override;
				void run(const Painter& painter, Cube& cube) override;

		private:
				struct PointShift { unsigned int x, y, z; unsigned int distance; bool slideUp; };

		private:
				void slide(RandomMultiShift::PointShift* points, size_t count, const Painter& painter, Cube& cube);

		private:
				unsigned int* z_cache = nullptr;
				PointShift* points = nullptr;
};

class SubCubes : public Animation {
		public:
				SubCubes() : Animation("spin sub cubes") {};
				virtual ~SubCubes();
				void init(Cube& cube) override;
				void run(const Painter& painter, Cube& cube) override;

		private:
				void moveSubCube(Pixel3d* subcube, Vector3d vector, Cube& cube);

		private:
				unsigned int _subcubeSide;
				Pixel3d* _subcube1 = nullptr;
				Pixel3d* _subcube2 = nullptr;
				Vector3d _direction1[6] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1} };
				Vector3d _direction2[6] = { {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
				unsigned int _steps;
};

#endif
