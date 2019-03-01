
#include "Headers/ManBearPig.h"

// task 8.2
typedef int (*First)(double);
typedef int* (*Second)(char const*);
typedef Second (*ComplexFunction)(int, First);

//8.3
template<class T, class R>
bool compare(const T& a, const T& b, R (T::*mptr)() const) {
    return (a.*mptr)() < (b.*mptr)();
}

template<class T>
bool isSameObject(T const* p, T const* q) {
    return dynamic_cast<const void*>(p) == dynamic_cast<const void*>(q);
}

int main() {
    ManBearPig p1(20, 60, 99, "QUKA");
    p1.makeNoise();
    p1.fellAsleep();
    p1.cookSmth();
    ManBearPig p2(13, 25, 86, "WWWW");
    std::cout << p1.health() << std::endl;
    std::string s1("Elf");
    std::string s2("Archer");
    std::cout << compare(s1, s2, &std::string::size) << std::endl;
    std::cout << compare(s1, s1, &std::string::size) << std::endl;
    Unit* First = &p1;
    Unit* Second = &p2;
    Bear* Third = &p1;
    std::cout << isSameObject<Unit>(First, Second) << std::endl;
    std::cout << isSameObject<Unit>(First, Third) << std::endl;
    return 0;
}