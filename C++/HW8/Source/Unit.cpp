#include "../Headers/Unit.h"

Unit::Unit(size_t id, size_t health, size_t damage, const std::string &noise) : mId(id), mHealth(health),
                                                                                mDamage(damage), mNoise(noise) {}

size_t Unit::id() const {
    return mId;
}

size_t Unit::health() const {
    return mHealth;
}

size_t Unit::damage() const {
    return mDamage;
}

void Unit::makeNoise() const {
    std::cout << mNoise << std::endl;
};