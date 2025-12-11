#include <iostream>
int main() {
    long long sum = 0;
    int x;
    while (std::cin >> x) {
        sum += x;
    }
    std::cout << sum << std::endl;
    return 0;
}
