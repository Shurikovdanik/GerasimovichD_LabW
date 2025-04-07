#include <iostream>

extern "C" long long func(long long x);

int main() {
    int x;
    std::cout << "Enter x: ";
    std::cin >> x;
    int sum = func(x);
    std::cout << "Res: " << sum << std::endl;
    return 0;
}
