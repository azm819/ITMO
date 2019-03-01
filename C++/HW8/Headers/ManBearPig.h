#pragma once

#include "Man.h"
#include "Bear.h"
#include "Pig.h"


class ManBearPig : public Man, public Bear, public Pig {
public:
    explicit ManBearPig(size_t id, size_t health, size_t damage, const std::string &noise);

    virtual ~ManBearPig() = default;
};