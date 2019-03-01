#pragma once

#include "Unit.h"

const size_t MAN_HEALTH = 150;
const size_t MAN_DAMAGE = 40;
const std::string MAN_NOISE = "I WANNA EAT";
const size_t MAN_FOOD = 13;

class Man : virtual public Unit{
public:
    explicit Man(size_t id, size_t health, size_t damage,const std::string &noise);
    void cookSmth();
    void setFood(size_t food);
    virtual ~Man() = default;

protected:
    size_t mFood;
};