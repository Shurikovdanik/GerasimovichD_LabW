#include <iostream>
#include "../include/Number.h"
#include "../include/Vector.h"
int main() {
    Number::Number a(0.77);
    Number::Number b(0.99);
    std::cout << (a + b).toDecimalString();
    return 0;
}