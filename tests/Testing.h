#ifndef __TESTING_H__
#define __TESTING_H__

#include <vector>

#ifdef ARDUINO

#ifdef NDEBUG
#define ASSERT(expr, msg) ((void)0)
#else
#define ASSERT(expr, msg) if(!(expr)) { Serial.print("FAILED ("); Serial.print(#expr); Serial.print("): "); Serial.println(msg); abort(); }
#endif

#else

#include <cassert>
#include <iostream>
#define ASSERT(expr, msg) if(!(expr)) { std::cerr << "FAILED (" << #expr << "): " << msg << std::endl; exit(1); }

#endif

class Test {
    public:
        virtual void run();

    protected:
        static void Register(Test* test);
        virtual const char* getName();

    private:
        static std::vector<Test*> _tests;
};

#define TEST(fixture, testName) class fixture##_##testName : public fixture {\
    public:\
        fixture##_##testName() { fixture::Register(this); };\
        void run() { testName(); }\
        void testName();\
} a##fixture##_##testName##_instance;\
void fixture##_##testName::testName()

#endif
