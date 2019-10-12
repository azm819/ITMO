#ifndef DES_UTILS_HPP
#define DES_UTILS_HPP

#include <stdint-gcc.h>
#include "tables.h"

void printBytes (uint64_t c, int size) {
    uint64_t b = 0;
    for (int i = 0; i < size; i++) {
        b <<= 1;
        b += (c % 2);
        c >>= 1;
    }
    for (int i = 0; i < size; i++) {
        std::cout << (b % 2);
        if (i % 8 == 7) std::cout << ' ';
        b >>= 1;
    }
    std::cout << '\n';
}

template <std::size_t N>
uint64_t permutation(uint64_t oldMes, const int (&table)[N], int size) {
    uint64_t bit, newMes = 0;
    uint64_t BITS[size + 1];
    for (int i = 1; i <= size; ++i) {
        BITS[size + 1 - i] = oldMes % 2;
        oldMes >>= 1;
    }
    for (auto i : table) {
        newMes <<= 1;
        newMes += BITS[i];
    }
    return newMes;
}

uint64_t makeShift(uint64_t N, int shifts) {
    while (shifts > 0) {
        uint64_t bit = N;
        bit >>= (SHIFT_2 - 1);
        uint64_t pow = 1;
        pow <<= (SHIFT_2 - 1);
        N = (N % pow);
        N <<= 1;
        N += bit;
        shifts--;
    }
    return N;
}

uint64_t S(uint64_t B, int index) {
    int first = B % 2;
    B >>= 1;
    int second = B % 16;
    B >>= 4;
    first = B * 2 + first;
    switch (index) {
        case 1:
            return S1[first * 16 + second];
        case 2:
            return S2[first * 16 + second];
        case 3:
            return S3[first * 16 + second];
        case 4:
            return S4[first * 16 + second];
        case 5:
            return S5[first * 16 + second];
        case 6:
            return S6[first * 16 + second];
        case 7:
            return S7[first * 16 + second];
        case 8:
            return S8[first * 16 + second];
        default:
            return 0;
    }
}

uint64_t f(uint64_t R, uint64_t K) {
    uint64_t TMP = K ^ permutation(R, E_TABLE, SHIFT_1);
    uint64_t B[9];
    uint64_t pow = 1;
    pow <<= 6;
    for (int i = 8; i >= 1; --i) {
        B[i] = TMP % pow;
        TMP >>= 6;
    }
    uint64_t RES = 0;
    for (int i = 1; i <= 8; ++i) {
        RES <<= 4;
        RES += S(B[i], i);
    }
    return permutation(RES, P, SHIFT_1);
}

#endif //DES_UTILS_HPP