#pragma once


#include <cstdio>
#include <algorithm>
#include <iostream>

template<class T>
class Array {
public:
    Array();

    explicit Array(size_t size, const T &value = T());
    Array(const Array<T> &array);
    Array &operator=(const Array &array);
    size_t size() const;
    T &operator[](size_t i);
    const T &operator[](size_t i) const;

    ~Array();

private :
    T *mData;
    size_t mSize{};
};
