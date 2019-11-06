#include <iostream>
#include "Utils.hpp"

const byte* key = reinterpret_cast<const unsigned char *>("Hello, World!");

int main() {
    KSA(key);
    byte* message = (unsigned char *) "HELLO!!!";
    std::cout << message << '\n';
    auto codedMess = code(message);
    std::cout << codedMess << '\n';
    KSA(key);
    auto decodedMess = code(codedMess);
    std::cout << decodedMess << '\n';
    delete(codedMess);
    delete(decodedMess);
    return 0;
}