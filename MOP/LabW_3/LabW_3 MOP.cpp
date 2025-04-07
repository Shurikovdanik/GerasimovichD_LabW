#include <cstdio>

// Объявление внешней ассемблерной функции (с соглашением C)
extern "C" long long FindSolutions();

int main() {
    // Вызов процедуры, которая выведет все решения уравнения и вернет их количество
    int count = FindSolutions();
    printf("Total number of solutions: %d\n", count);
    return 0;
}
