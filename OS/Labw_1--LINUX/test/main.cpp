#include <iostream>
#include "../include/Number.h"
#include "../include/Vector.h"
int main() {

    Numbers::Number a(0.5);
    a = Numbers::Number::fromString("1.5e0", Numbers::systems::BASE_TEN);
    Numbers::Number b(2.30f);
    b = Numbers::Number::fromString("1.5e0", Numbers::systems::BASE_TEN);
    return 0;
}