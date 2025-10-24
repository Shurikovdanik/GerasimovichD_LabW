#include <iostream>
#include "../include/Matrix.h"
#include "../include/Number.h"
using Num = float;

int main() {
    Num** a = new Num*[2];
    Num** b = new Num*[2];
    for (int i = 0; i < 2; ++i) {
        a[i] = new Num[2]{1, 1};
        b[i] = new Num[2]{2, 2};
    }
    Matrix A(a, 2, 2);
    Matrix B(b, 2, 2);
    std::cout << A.toString() << "\n \n" << B.toString();
    std::cout << (A * B).toString();
    std::cout << std::thread::hardware_concurrency();

}