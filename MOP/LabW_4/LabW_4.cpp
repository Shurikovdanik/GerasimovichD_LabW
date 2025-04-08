#include <iostream>

extern "C" double __stdcall CalculatePI();
int main() {
    std::cout << CalculatePI();
    return 0;
}
