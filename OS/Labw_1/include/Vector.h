#pragma once

#include "Number.h"
namespace Algebra {
class Vector {
    private:
    Number::Number* scalars;

    public:
    Vector(Number::Number* args) {
        this->scalars = args;
    }
    int dimensions() {
        return sizeof(scalars) / sizeof(Number::Number);
    }
    Number::Number EuclNorma() {
        Number::Number res = 0;
        for (int i = 0; i < dimensions(); i++) {
            res = res + scalars[i];
        }
        res = res.sqrt();
    }
};
}