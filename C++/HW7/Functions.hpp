#pragma once

#include "Functions.h"

template<class T>
bool Greater::operator()(T a, T b) const {
    return a > b;
}

template<class T>
bool less(T a, T b) {
    return a < b;
}

template<class T, class C>
T minimum(const Array<T> &array, C comparator) {
    T minimum = array[0];
    for (int i = 0; i < array.size(); ++i) {
        if (comparator(array[i], minimum)) {
            minimum = array[i];
        }
    }
    return minimum;
}

template<class T>
void flatten(const T &element, std::ostream &out) {
    out << element << " ";
}

template<class T>
void flatten(const Array<T> &array, std::ostream &out) {
    for (int i = 0; i < array.size(); ++i) {
        flatten(array[i], out);
    }
}