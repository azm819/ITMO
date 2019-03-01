#include "../Headers/Animal.h"

std::string const &Animal::name() const { return mName; }

Animal::Animal(const std::string &name, size_t id, size_t health, size_t damage,
               const std::string &noise = ANIMAL_NOISE)
        : Unit(id, health, damage, noise), mName(name) {}

