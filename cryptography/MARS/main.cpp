#include <iostream>
#include "utils.hpp"

using std::cout;

void printMessage(const vector<uint32_t> &message) {
//    cout << (message[_A]   message[_B]  message[_C]  message[_D]) << '\n';
}

void encrypt(vector<uint32_t> &message, vector<uint32_t> &key) {
    cout << "Encrypting...\n";
    firstAddingKeys(message, key);
    directMixing(message);
    cryptoConversion(message, key);
    reverseMixing(message);
    lastAddingKeys(message, key);
    cout << "Encrypted: \n";
    cout << message[_A] << ' ' << message[_B] << ' ' << message[_C] << ' ' << ' ' << message[_D] << '\n';
}

int main() {
    cout << std::hex;
    vector<uint32_t > message = {0xff654ab6, 0xabcd5454, 0x45, 0xbb789556};

    return 0;
}