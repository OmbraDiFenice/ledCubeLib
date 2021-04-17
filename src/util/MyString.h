#ifndef __MYSTRING_H__
#define __MYSTRING_H__

class MyString {
    public:
        MyString();
        MyString(const char* str);
        MyString(const MyString& other);
        ~MyString();

        char* get() const;
        unsigned int length();
        
        MyString& append(const MyString& other);

        bool operator==(const MyString& other) const;
        inline bool operator!=(const MyString& other) const { return !(*this == other); };

    private:
        char* _buf;
        unsigned int _len;
};

#endif
