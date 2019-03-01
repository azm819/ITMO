#include "../Headers/Man.h"

Man::Man(size_t id, size_t health = MAN_HEALTH, size_t damage = MAN_DAMAGE, const std::string &noise = MAN_NOISE)
        : Unit(id, health, damage, noise), mFood(MAN_FOOD) {}

void Man::setFood(size_t food) {
    mFood = food;
}

void Man::cookSmth() {
    std::cout << "Mmm, tasty" << std::endl;
}

