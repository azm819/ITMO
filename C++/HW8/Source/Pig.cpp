#include "../Headers/Pig.h"

Pig::Pig(size_t id, size_t health = PIG_HEALTH, size_t damage = PIG_DAMAGE, const std::string &noise = PIG_NOISE)
        : Unit(id, health, damage, noise), Animal("pig", id, health, damage, noise) {
    mAcorns = PIG_ACORNS;
}

void Pig::setAcorns(size_t acorns) {
    mAcorns = acorns;
}
