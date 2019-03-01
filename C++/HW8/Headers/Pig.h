#pragma once

#include "Animal.h"

const size_t PIG_HEALTH = 100;
const size_t PIG_DAMAGE = 30;
const std::string PIG_NOISE = "HRIU";
const size_t PIG_ACORNS = 18;

class Pig : virtual public Animal {
public:
    explicit Pig(size_t id, size_t health, size_t damage, const std::string &noise);

    void setAcorns(size_t acorns);

    virtual ~Pig() = default;

protected:
    size_t mAcorns;
};