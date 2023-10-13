#include <util/MyString.h>

#ifdef ARDUINO
    #include <string.h>
#else
    #include <cstring>
    using std::strcpy;
    using std::strcmp;
    using std::memcpy;
#endif

MyString::MyString() {
    _len = 0;
    _buf = new char[1];
    _buf[0] = '\0';
}

MyString::MyString(const char* str) {
    _len = strlen(str);
    _buf = new char[_len+1];
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

char* MyString::get() const {
    return _buf;
}

unsigned int MyString::length() {
    return _len;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(_buf, other._buf) == 0;
}

MyString& MyString::append(const MyString& other) {
    char* tmp = new char[_len + other._len + 1];
    memcpy(tmp, _buf, _len);
    delete _buf;
    memcpy(&tmp[_len], other._buf, other._len + 1);
    _len = _len + other._len;
    _buf = tmp;
    return *this;
}
