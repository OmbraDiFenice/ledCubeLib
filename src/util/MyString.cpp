#include <util/MyString.h>

#ifdef ARDUINO
    #include <string.h>
#else
    #include <cstring>
    using std::strcpy;
#endif

MyString::MyString() {
    _len = 0;
    _buf = new char[1];
    _buf[0] = '\0';
}

MyString::MyString(const char* str) {
    _len = strlen(str);
    _buf = new char[_len];
    strcpy(_buf, str);
}

MyString::MyString(const MyString& other) {
    _len = other._len;
    _buf = new char[_len];
    strcpy(_buf, other._buf);
}

MyString::~MyString() {
    delete _buf;
}

char* MyString::get() {
    return _buf;
}

unsigned int MyString::length() {
    return _len;
}
