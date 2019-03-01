#include "../Headers/ManBearPig.h"

ManBearPig::ManBearPig(size_t id, size_t health, size_t damage, const std::string &noise) : Unit(id, health, damage,
                                                                                                 noise),
                                                                                            Man(id, health, damage,
                                                                                                noise),
                                                                                            Animal("ManBearPig", id,
                                                                                                   health, damage,
                                                                                                   noise),
                                                                                            Bear(id, health, damage,
                                                                                                 noise),
                                                                                            Pig(id, health, damage,
                                                                                                noise) {}

