#include "TestVector.h"

TEST(TestVector, startEmpty) {
    Vector<int> v;
    ASSERT(0 == v.capacity(), "capacity should be 0");
    ASSERT(1 == v.size(), "size should be 1");
}
