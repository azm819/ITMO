#pragma once

#include "Array.h"

template<class T>
Array<T>::Array() {
    mSize = 0;
    mData = nullptr;
}

template<class T>
Array<T>::Array(size_t size, const T &value) : mSize(size), mData(reinterpret_cast<T *>(new char[size * sizeof(T)])) {
    for (size_t i = 0; i < size; ++i) {
        new(mData + i) T(value);
    }
}

template<class T>
Array<T>::Array(const Array &array) {
    if (array.mSize) {
        mSize = array.mSize;
        mData = reinterpret_cast <T *>(new char[mSize * sizeof(T)]);
        for (size_t i = 0; i < mSize; ++i) {
            new(mData + i) T(array[i]);
        }
    } else {
        mData = nullptr;
        mSize = 0;
    }
}

template<class T>
Array<T> &Array<T>::operator=(const Array &array) {
    if (this != &array) {
        for (int i = 0; i < mSize; i++) {
            mData[i].~T();
        }
        delete[](char *) mData;
        mSize = array.size();
        mData = reinterpret_cast <T *>(new char[mSize * sizeof(T)]);
        for (size_t i = 0; i < mSize; ++i) {
            new(mData + i) T(array[i]);
        }
    }
    return *this;
}

template<class T>
size_t Array<T>::size() const {
    return mSize;
}

template<class T>
T &Array<T>::operator[](size_t i) {
    return mData[i];
}

template<class T>
const T &Array<T>::operator[](size_t i) const {
    return mData[i];
}

template<class T>
Array<T>::~Array() {
    for (int i = 0; i < mSize; i++) {
        mData[i].~T();
    }
    delete[](char *) mData;
}