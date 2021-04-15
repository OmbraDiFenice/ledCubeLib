#include <util/TestVector.h>

TEST(TestVector, startEmpty) {
    ASSERT(1u == vec.capacity(), "incorrect capacity");
    ASSERT(0u == vec.size(), "incorrect size");
}

TEST(TestVector, append1) {
    vec.append(1);

    ASSERT(1u == vec.capacity(), "incorrect capacity");
    ASSERT(1u == vec.size(), "incorrect size");
    ASSERT(1 == vec.at(0), "incorrect value in vector");
}

TEST(TestVector, append2) {
    vec.append(1);
    vec.append(2);

    ASSERT(2u == vec.capacity(), "incorrect capacity");
    ASSERT(2u == vec.size(), "incorrect size");
    ASSERT(1 == vec.at(0), "incorrect value in vector");
    ASSERT(2 == vec.at(1), "incorrect value in vector");
}

TEST(TestVector, append5_doubleCapacity) {
    vec.append(1);
    vec.append(2);
    vec.append(3);
    vec.append(4);
    vec.append(5);

    ASSERT(8u == vec.capacity(), "incorrect capacity");
    ASSERT(5u == vec.size(), "incorrect size");
    ASSERT(1 == vec.at(0), "incorrect value in vector");
    ASSERT(2 == vec.at(1), "incorrect value in vector");
    ASSERT(3 == vec.at(2), "incorrect value in vector");
    ASSERT(4 == vec.at(3), "incorrect value in vector");
    ASSERT(5 == vec.at(4), "incorrect value in vector");
}

TEST(TestVector, indexOutOfBounds) {
    try {
        vec.at(0);
        ASSERT(false, "exception should have been thrown");
    } catch(...) {
        ASSERT(true, "exception not thrown");
    }
}
