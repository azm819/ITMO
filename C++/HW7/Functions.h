#pragma once

#include "Array.h"

class Greater {
public:
    template<class T>
    bool operator()(T a, T b) const;
};

template<class T>
bool less(T a, T b);

template<class T, class C>
T minimum(const Array<T> &array, C comp);

template<class T>
void flatten(const T &element, std::ostream &out);

template<class T>
void flatten(const Array<T> &array, std::ostream &out);