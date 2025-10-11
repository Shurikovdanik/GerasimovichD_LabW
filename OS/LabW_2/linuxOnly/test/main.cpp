#include "../include/Matrix.h"
#include "../include/Number.h"
using Num = float;

int main() {
    Num a[3] = {1, 2, 3};
    Num b[3] = {4, 5, 6};
    
    Num* res = Matrix::arrrayMul(a, b, 3);


}