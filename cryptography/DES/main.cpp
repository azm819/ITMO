
#include <stdint-gcc.h>
#include "encryptor.hpp"
#include "decryptor.hpp"

int main () {
    uint64_t M = 81985529216486895;
    M = 897987987989879878;
    M = 0xAAAAAAAAAAAAAAAA;
    M = 0xFEDCBA9876543210;
    uint64_t key = 1383827165325090801;
    key = 0xFEDCBA9876543210;
    decryptor(key, encryptor(key, M));
    return 0;
}
