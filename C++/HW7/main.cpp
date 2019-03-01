#include "Tests.h"

int main() {
    Array<int> ints(3, 0);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less<int>);
    int max = minimum(ints, Greater());
    std::cout << min << " " << max << "\n";

    Array<int> ints1(2, 0);
    ints1[0] = 10;
    ints1[1] = 20;
    flatten(ints1, std::cout); // выводит на экран строку "10 20"
    Array<Array<int>> array_of_ints(2, ints1);
    std::cout << "\n";
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
    std::cout << "\n";
    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout);
    test();
    return 0;
}