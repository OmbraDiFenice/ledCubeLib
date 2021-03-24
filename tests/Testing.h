#ifndef __TESTING_H__
#define __TESTING_H__

#ifdef ARDUINO

#ifdef NDEBUG
#define ASSERT(expr, msg) ((void)0)
#else
#define ASSERT(expr, msg) if(!(expr)) { Serial.print("Assertion failed: "); Serial.print(#expr); Serial.print(" at "); Serial.println(msg); abort(); }
#endif

#else

#include <cassert>
#define ASSERT(expr, msg) assert(((void)msg, expr))

#endif

#endif
