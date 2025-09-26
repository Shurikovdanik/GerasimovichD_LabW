#include <iostream>
#include "../include/Number.h"
#include "../include/Vector.h"
int main() {

    Number::Number a(0.5);
    a = Number::Number::fromString("1.5e0", Number::systems::BASE_TEN);
    Number::Number b(2.30f);
    b = Number::Number::fromString("1.5e0", Number::systems::BASE_TEN);
    return 0;
}