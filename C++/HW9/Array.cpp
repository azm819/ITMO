#include "Array.h"

template<class T>
Array<T>::Array(size_t size) {
    mSize = size;
    mData = new T[size];
}

template<class T>
Array<T>::Array(Array<T> const &array) : mSize(array.size()) {
    delete[] mData;
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; ++i) {
        mData = array[i];
    }
}

template<class T>
Array<T>::Array(Array<T> &&array) : mData(nullptr), mSize(0) {
    mData = array.mData;
    mSize = array.mSize;
    array.mData = nullptr;
    array.mSize = 0;
}

template<class T>
Array<T> &Array<T>::operator=(Array const &array) {
    delete[] mData;
    mSize = array.size();
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; ++i) {
        mData[i] = array[i];
    }
    return *this;
}

template<class T>
size_t Array<T>::size() const {
    return mSize;
}

template<class T>
Array<T> &Array<T>::operator=(Array<T> &&array) {
    if (this != array) {
        delete[] mData;
        mData = array.mData;
        mSize = array.mSize;
        array.mData = nullptr;
        array.mSize = 0;
    }
    return *this;
}

template<class T>
T &Array<T>::operator[](size_t i) {
    return mData[i];
}

template<class T>
T const &Array<T>::operator[](size_t i) const {
    return mData[i];
}

template<class T>
Array<T>::~Array() {
    delete[] mData;
}