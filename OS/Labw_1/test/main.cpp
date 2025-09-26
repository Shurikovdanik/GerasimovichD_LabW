#include <iostream>
#include "../include/Number.h"
#include "../include/Vector.h"
int main() {

    Number::Number a(1.0);
    a = Number::Number::fromString("1.0");
    Number::Number b(1.0);
    b.setFormat(Number::systems::BASE_TWO);
    b = Number::Number::fromString("14e-2", Number::systems::BASE_TEN);
    b.setFormat(Number::systems::BASE_TEN);
    std::cout << b.getMantissa() << " " << b.getExponenta() <<" " << b.toDecimalString();
    return 0;
}