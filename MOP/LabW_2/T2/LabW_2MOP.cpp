#include <iostream>


extern "C" int SumLastDigits(int n, int m);

int main() {
    int n, m;
    std::cout << "Enter n, m";
    std::cin >> n >> m;

    int result = SumLastDigits(n, m);
    std::cout << "Summ of " << m << " last digits of " << n << " = " << result << std::endl;
    return 0;
}
