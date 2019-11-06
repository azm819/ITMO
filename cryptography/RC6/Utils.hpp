#ifndef RC6_UTILS_HPP
#define RC6_UTILS_HPP

#include <vector>
#include <cstdint>
#include <cmath>

using std::vector;

#define Word vector<uint32_t>

const uint32_t P_32 = 0xb7e15163;
const uint32_t Q_32 = 0x9e3779b9;

const uint32_t WORD_SIZE = 32;
const size_t KEY_SIZE = 44;
const uint32_t SMALL_SHIFT = 3;
const uint32_t BIG_SHIFT = 5;
const size_t ROUND_NUM = 20;

const size_t _A = 0;
const size_t _B = 1;
const size_t _C = 2;
const size_t _D = 3;

void rightShift(uint32_t &I, uint32_t bits) {
    bits %= WORD_SIZE;
    uint32_t tmp = I;
    tmp <<= (WORD_SIZE - bits);
    I >>= bits;
    I |= tmp;
}

void leftShift(uint32_t &I, uint32_t bits) {
    bits %= WORD_SIZE;
    uint32_t tmp = I;
    tmp >>= (WORD_SIZE - bits);
    I <<= bits;
    I |= tmp;
}

Word keyExtension(Word &base) {
    Word key(KEY_SIZE);

    key[0] = P_32;

    for (size_t i = 1; i < KEY_SIZE; ++i) {
        key[i] = key[i - 1] + Q_32;
    }

    size_t size = base.size();

    size_t iterations = size * SMALL_SHIFT;

    size_t i = 0, j = 0;
    uint32_t A = 0, B = 0;

    while (iterations--) {
        key[i] += A + B;
        leftShift(key[i], SMALL_SHIFT);
        A = key[i];

        base[j] += A + B;
        leftShift(base[j], A + B);
        B = base[j];

        i = (i + 1) % KEY_SIZE;
        j = (j + 1) % size;
    }

    return key;
}

uint32_t f(uint32_t X) {
    return X * (2 * X + 1);
}

void encrypt(Word &message, Word &key) {
    message[_B] += key[0];
    message[_D] += key[1];

    for (size_t round = 1; round <= ROUND_NUM; ++round) {
        uint32_t A = message[_A];
        uint32_t B = message[_B];
        uint32_t C = message[_C];
        uint32_t D = message[_D];

        uint32_t temp1 = f(B);
        leftShift(temp1, BIG_SHIFT);

        uint32_t temp2 = f(D);
        leftShift(temp2, BIG_SHIFT);

        A ^= temp1;
        leftShift(A, temp2);
        A += key[2 * round];

        C ^= temp2;
        leftShift(C, temp1);
        C += key[2 * round + 1];

        message[_A] = B;
        message[_B] = C;
        message[_C] = D;
        message[_D] = A;
    }

    message[_A] += key[42];
    message[_C] += key[43];
}

void decrypt(Word &message, Word &key) {
    message[_A] -= key[42];
    message[_C] -= key[43];

    for (size_t round = ROUND_NUM; round >= 1; --round) {
        uint32_t A = message[_D];
        uint32_t B = message[_A];
        uint32_t C = message[_B];
        uint32_t D = message[_C];

        uint32_t temp1 = f(B);
        leftShift(temp1, BIG_SHIFT);

        uint32_t temp2 = f(D);
        leftShift(temp2, BIG_SHIFT);

        A -= key[2 * round];
        rightShift(A, temp2);
        A ^= temp1;

        C -= key[2 * round + 1];
        rightShift(C, temp1);
        C ^= temp2;

        message[_A] = A;
        message[_B] = B;
        message[_C] = C;
        message[_D] = D;
    }

    message[_B] -= key[0];
    message[_D] -= key[1];
}

void print(Word &word) {
    for (unsigned int i : word) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

#endif //RC6_UTILS_HPP
