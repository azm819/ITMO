#include <utility>
#include <iostream>

template<class T>
struct Array {
    explicit Array(size_t size = 0);
    Array(Array const& array);
    Array(Array && array); // перемещающий конструктор

    Array & operator=(Array const& array);
    size_t size() const;
    Array & operator=(Array && array); // перемещающий оператор копирования
    T &         operator[](size_t i);
    T const&    operator[](size_t i) const;

    ~Array();
private:
    size_t  mSize;
    T *     mData;
};