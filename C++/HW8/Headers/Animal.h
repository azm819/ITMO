#pragma once

#include "Unit.h"

const std::string ANIMAL_NOISE = "UUUUUUUUUUUUUUUU";

class Animal : virtual public Unit{
public:
    Animal(std::string const& name, size_t id, size_t health, size_t damage,const std::string &noise);
    std::string const& name() const;
    virtual ~Animal() = default;
protected:
    std::string mName;
};