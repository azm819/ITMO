#include "../Headers/Bear.h"

Bear::Bear(size_t id, size_t health = BEAR_HEALTH, size_t damage = BEAR_DAMAGE, const std::string &noise = BEAR_NOISE)
        : Unit(id, health, damage, noise), Animal("bear", id, health, damage, noise) {
    mFat = BEAR_FAT;
}

void Bear::fellAsleep() {
    std::cout << "ZZZzzzZZzzZz" << std::endl;
}

void Bear::setFat(size_t fat) {
    mFat = fat;
}
