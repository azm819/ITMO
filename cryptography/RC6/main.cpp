#include <iostream>
#include "Utils.hpp"

int main() {
    Word key{1, 2, 3, 5};
    key = keyExtension(key);
    Word message{546545, 2, 3, 565456};
    std::cout << "Message : ";
    print(message);
    encrypt(message, key);
    std::cout << "Coded message : ";
    print(message);
    decrypt(message, key);
    std::cout << "Decoded message : ";
    print(message);
    return 0;
}