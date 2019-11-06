#ifndef RC4_UTILS_HPP
#define RC4_UTILS_HPP

#include <glob.h>
#include <array>

#define byte unsigned char

const size_t SIZE = 256;
const size_t SIZE_OF_BYTE = sizeof(byte);

byte S[SIZE];

byte first = 0;
byte second = 0;

void KSA(const byte *key) {
    for (size_t i = 0; i < SIZE; ++i) {
        S[i] = i;
    }

    byte j = 0;
    size_t size = sizeof(key) / SIZE_OF_BYTE;

    for (size_t i = 0; i < SIZE; ++i) {
        j = (j + S[i] + key[i % size]) % SIZE;
        std::swap(S[i], S[j]);
    }
}

byte PRGA() {
    first = (first + 1) % SIZE;
    second = (second + S[first]) % SIZE;
    std::swap(S[first], S[second]);
    return S[(S[first] + S[second]) % SIZE];
}

byte *code(const byte *message) {
    first = second = 0;
    size_t size = sizeof(message) / SIZE_OF_BYTE;
//    std::cout << message << '\n';
    byte *res = new byte[size];

    for (size_t i = 0; i < size; ++i) {
        res[i] = message[i] ^ PRGA();
    }
    return res;
}

#endif //RC4_UTILS_HPP
