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

TEST(TestString, not_equals) {
    MyString a("A");
    MyString b("B");
    ASSERT(!(a == b), "should not compare equal");
    ASSERT(a != b, "should not compare equal");
}

TEST(TestString, equals) {
    MyString a("String");
    MyString b("String");
    ASSERT(a == b, "should compare equal");
}

TEST(TestString, append) {
    MyString s1;
    s1.append("test");
    MyString expected1("test");
    ASSERT(expected1 == s1, "should be equal");
    ASSERT(4u == s1.length(), "wrong length");

    MyString s2("a");
    s2.append(" test");
    MyString expected2("a test");
    ASSERT(expected2 == s2, "should be equal");
    ASSERT(6u == s2.length(), "wrong length");

    s2.append(" 2");
    MyString expected3("a test 2");
    ASSERT(expected3 == s2, "should be equal");
    ASSERT(8u == s2.length(), "wrong length");
}
