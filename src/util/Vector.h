#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef ARDUINO
    #include <string.h>
#else
    #include <cstring>
    using std::memcpy;
#endif

template<typename T>
class Vector {
    public:
        Vector() { init(1); };
        Vector(unsigned int initialCapacity) { init(initialCapacity); };
        ~Vector() { delete[] _vec; };

        inline unsigned int capacity() { return _capacity; };
        inline unsigned int size() { return _size; };

        void append(T&& elem);
        inline T& at(unsigned int index) {
            if(index >= _size) throw "index out of bounds";
            return _vec[index];
        };

    private:
        void init(unsigned int initialCapacity) {
            _capacity = initialCapacity;
            _size = 0;
            _vec = new T[_capacity];
        };
        
    private:
        unsigned int _capacity;
        unsigned int _size;
        T* _vec;
};

template<typename T>
void Vector<T>::append(T&& elem) {
    if(_size >= _capacity) {
        _capacity *= 2;
        T* tmp = new T[_capacity];
        memcpy(tmp, _vec, (_capacity / 2) * sizeof(T));
        delete[] _vec;
        _vec = tmp;
    } 
    _vec[_size++] = T{elem};
}

#endif
