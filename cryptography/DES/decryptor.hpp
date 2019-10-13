#include <iostream>
#include "utils.hpp"

uint64_t decryptor(uint64_t key, uint64_t M) {
    std::cout << "Decryptor is working...\n";
    std::cout << "key : ";
    printBytes(key, 64);
    std::cout << "coded message : ";
    printBytes(M, 64);
    uint64_t C[17], D[17], K[17], L[17], R[17];

    // FIRST STEP
    uint64_t newKey = permutation(key, PC_1, MAX_POW_1);
    C[0] = newKey >> SHIFT_2;
    uint64_t pow = 1;
    pow <<= SHIFT_2;
    D[0] = newKey % pow;
    for (int i = 1; i <= 16; ++i) {
        C[i] = makeShift(C[i - 1], iteration[i]);
        D[i] = makeShift(D[i - 1], iteration[i]);
        K[i] = (C[i] << 28) + D[i];
        K[i] = permutation(K[i], PC_2, MAX_POW_2);
    }

    for (int i = 1; i <= 8; ++i) {
        uint64_t tmp = K[i];
        K[i] = K[16 - i + 1];
        K[16 - i + 1] = tmp;
    }

    // SECOND STEP
    uint64_t IPS = permutation(M, IP, MAX_POW_1);
    L[0] = IPS >> SHIFT_1;
    pow = 1;
    pow <<= SHIFT_1;
    R[0] = IPS % pow;
    for (int i = 1; i <= 16; ++i) {
        L[i] = R[i - 1];
        R[i] = L[i - 1] ^ f(R[i - 1], K[i]);
    }
    uint64_t RES = R[16];
    RES <<= 32;
    RES += L[16];
    RES = permutation(RES, reversedIP, MAX_POW_1);
    std::cout << "---------------- Result ----------------\nBinary : ";
    printBytes(RES, 64);
    std::cout << "Decimal : " << RES << '\n';
    std::cout << "Decryptor stopped.\n\n";

    return 0;
}