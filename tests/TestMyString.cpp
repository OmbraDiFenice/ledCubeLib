#include "TestMyString.h"

#ifdef ARDUINO
    #include <string.h>
#else
    #include <cstring>
    using std::strcmp;
#endif

TEST(TestString, startEmpty) {
    MyString s;
    ASSERT(0 == strcmp("", s.get()), "string should be empty");
}

TEST(TestString, copy) {
    MyString a("String 1");
    MyString b = a;
    ASSERT(0 == strcmp(a.get(), b.get()), "strings should be equal");
    ASSERT(a.length() == b.length(), "length should match");
}

TEST(TestString, length) {
    MyString s("String");
    ASSERT(6u == s.length(), "length does not match");
}
