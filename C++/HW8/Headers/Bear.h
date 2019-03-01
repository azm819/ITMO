#pragma once

#include "Animal.h"

const size_t BEAR_HEALTH = 200;
const size_t BEAR_DAMAGE = 50;
const std::string BEAR_NOISE = "ARGH";
const size_t BEAR_FAT = 10;

class Bear : virtual public Animal{
public:
    explicit Bear(size_t id, size_t health, size_t damage,const std::string &noise);
    void fellAsleep();
    void setFat(size_t fat);
    virtual ~Bear() = default;

protected:
    size_t mFat;
};