#include <vector>
#include "tables.h"

using std::vector;

//#define DECLARATION(A, B, C, D) {uint32_t A = message[_A];\
//uint32_t B = message[_B];\
//                             uint32_t C = message[_C];\
//                             uint32_t D = message[_D];}

const size_t _A = 0;
const size_t _B = 1;
const size_t _C = 2;
const size_t _D = 3;

const int ROUND_NUM = 8;

const uint32_t SMALL_SHIFT = 8;
const uint32_t BIG_SHIFT = 13;

const uint32_t MAX_5 = 31;
const uint32_t MAX_8 = 255;
const uint32_t MAX_9 = 511;

void rightShift(uint32_t &I, uint32_t bits) {
    uint32_t tmp = I;
    tmp <<= (32 - bits);
    I >>= bits;
    I |= tmp;
}

void leftShift(uint32_t &I, uint32_t bits) {
    uint32_t tmp = I;
    tmp >>= (32 - bits);
    I <<= bits;
    I |= tmp;
}

void E(vector<uint32_t> &O, uint32_t A, vector<uint32_t> &key, int round) {
    auto O1 = A, O2 = A;
    O1 += key[2 * round + 4];
    leftShift(O2, BIG_SHIFT);
    O2 *= key[2 * round + 5];
    auto index = O1 & MAX_9;
    uint32_t O3;
    if (index < 256) {
        O3 = S0[index];
    } else {
        O3 = S1[index % 256];
    }
    leftShift(O1, O2 & MAX_5);
    O3 ^= O2;
    leftShift(O2, 5);
    O3 ^= O2;
    leftShift(O1, O2 & MAX_5);
    O[1] = O1;
    O[2] = O2;
    O[3] = O3;
}

void firstAddingKeys(vector<uint32_t> &message, vector<uint32_t> &key) {
    for (int i = 0; i < 4; ++i) {
        message[i] += key[i];
    }
}

void directMixing(vector<uint32_t> &message) {
    for (int round = 0; round < ROUND_NUM; ++round) {
        uint32_t A = message[_A];
        uint32_t B = message[_B];
        uint32_t C = message[_C];
        uint32_t D = message[_D];

        B ^= S0[A & MAX_8];
        rightShift(A, SMALL_SHIFT);
        B += S1[A & MAX_8];
        rightShift(A, SMALL_SHIFT);
        C += S0[A & MAX_8];
        rightShift(A, SMALL_SHIFT);
        D ^= S1[A & MAX_8];

        if (round == 0 || round == 4) {
            A += D;
        }

        if (round == 1 || round == 5) {
            A += B;
        }

        message[_A] = B;
        message[_B] = C;
        message[_C] = D;
        message[_D] = A;
    }
}

void cryptoConversion(vector<uint32_t> &message, vector<uint32_t> &key) {
    vector<uint32_t> O;
    for (int round = 0; round < ROUND_NUM * 2; ++round) {
        uint32_t A = message[_A];
        uint32_t B = message[_B];
        uint32_t C = message[_C];
        uint32_t D = message[_D];

        E(O, message[_A], key, round);
        leftShift(A, BIG_SHIFT);
        C += O[1];
        if (round < ROUND_NUM) {
            B += O[0];
            D ^= O[2];
        } else {
            B += O[2];
            D += O[0];
        }

        message[_A] = B;
        message[_B] = C;
        message[_C] = D;
        message[_D] = A;
    }
}

void reverseMixing(vector<uint32_t> &message) {
    for (int round = 0; round < ROUND_NUM; ++round) {
        uint32_t A = message[_A];
        uint32_t B = message[_B];
        uint32_t C = message[_C];
        uint32_t D = message[_D];

        B ^= S1[A & MAX_8];
        leftShift(A, SMALL_SHIFT);
        C -= S0[A & MAX_8];
        leftShift(A, SMALL_SHIFT);
        D -= S1[A & MAX_8];
        leftShift(A, SMALL_SHIFT);
        D ^= S0[A & MAX_8];

        if (round == 1 || round == 5) {
            B -= A;
        }

        if (round == 2 || round == 6) {
            B -= C;
        }

        message[_A] = B;
        message[_B] = C;
        message[_C] = D;
        message[_D] = A;
    }
}

void lastAddingKeys(vector<uint32_t> &message, vector<uint32_t> &key) {
    for (int i = 36; i < 40; ++i) {
        message[i - 36] += key[i % key.size()];
    }
}