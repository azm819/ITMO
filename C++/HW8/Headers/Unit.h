#pragma once

#include <iostream>

class Unit {
public:
    explicit Unit(size_t id, size_t health, size_t damage, const std::string &noise);

    size_t id() const;

    size_t health() const;

    size_t damage() const;

    void makeNoise() const;

    virtual ~Unit() = default;

private:
    size_t mId;
    size_t mHealth;
    size_t mDamage;
    std::string mNoise;
};