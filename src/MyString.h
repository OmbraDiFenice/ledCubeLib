#ifndef __MYSTRING_H__
#define __MYSTRING_H__

class MyString {
    public:
        MyString();
        MyString(const char* str);
        MyString(const MyString& other);
        ~MyString();

        char* get();
        unsigned int length();

    private:
        char* _buf;
        unsigned int _len;
};

#endif
