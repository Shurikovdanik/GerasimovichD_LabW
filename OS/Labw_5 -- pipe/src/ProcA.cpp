#include <iostream>
int main() {
    const int N = 6;
    int x;
    while (std::cin >> x) {
        std::cout << x + N << " ";
    }
    return 0;
}
