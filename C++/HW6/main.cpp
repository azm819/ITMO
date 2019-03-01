#include "Item.h"

int main() {
    Item milk(8, 145, 3, "Milk", "Russia", 5, 9, 17);
    Item ex(5, 500000, 8, "Car", "Germany", 15, 40, 23);
    ex = milk;
    std::cout << ex << std::endl;
    Item car(5, 500000, 8, "Car", "Germany", 15, 40, 23);
    ex = car + milk;
    std::cout << ex << std::endl;
    ex = car - milk;
    std::cout << ex << std::endl;
    ex = car * milk;
    std::cout << ex << std::endl;
    ex = car / milk;
    std::cout << ex << std::endl;
    bool t = car == milk;
    std::cout << t << std::endl;
    t = car != milk;
    std::cout << t << std::endl;
    t = car[10];
    std::cout << t << std::endl;
    t = car[1000000000];
    std::cout << t << std::endl;
}
