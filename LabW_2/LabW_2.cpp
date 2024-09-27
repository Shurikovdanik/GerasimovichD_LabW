#include <iostream>
#include <ctime>
#include <cstdlib>
void Input(double *a, int num) // функция ввода значений в массив (массив а)
{
    bool isAuto;
    std::cout << std::endl << "0 to manually fill array, 1 to fill it with random numbers: ";
    std::cin >> isAuto;
    if (isAuto) // Генерация случайных чисел (в описанных пределах. До 3 знаков после запятой включительно)
    {
        srand(static_cast<unsigned int>(time(0)));
        double min, max;
        std::cout << std::endl
                  << "Minimum and maximum possible numbers: ";
        std::cin >> min >> max;
        for (int i = 0; i < num; i++) {
            a[i] = (rand() % (int)(max * 1000 - min * 1000) + (int)min * 1000) / 1000.0;
            std::cout << a[i] << " ";
        }
    }
    else
        for (int i = 0; i < num; i++) // ручной ввод с консоли
        {
            std::cin >> a[i];
        }
}
bool Mod_comparator(double a, double b) // функция сравнения двух чисел |a| и |b|; а, b действительные
{
    bool res;
    if (a < 0){
        a -= 2 * a;
    }
    if (b < 0){
        b -= 2 * b;
    }
    return (a > b);
}
int searchForTheBiggest(double *a, int num, bool isTheBiggest) // функция, возвращающая номер - 1 крайнего значения в массиве а по сравнению по модулю
{
    int m = 0;
    for (int i = 0; i < num; i++){
        if (Mod_comparator(a[m], a[i]) != isTheBiggest)
        {
            m = i;
        }
    }
    return m;
}
int searchForMoreThanZero(double *a, int num, int start) // возвращает номер первого >0 элемента после элемента с номером start
{
    int res = -1;
    for (int i = start; i < num; i++) {
        if (a[i] > 0) {
            res = i;
            break;
        }
    }
    return res;
}
double Summa(double *a, int num, int start, int finish) // Суммма всех элементов от элемента с номером start до элемента с номером finish не включительно
{
    double res = 0;
    for (int i = start; i <= finish; i++) {
        res += a[i];
    }
    return res;
}
void ccout(double *a, int num) // вывод массива
{
    std::cout << std::endl;
    for (int i = 0; i < num; i++) {
        std::cout << a[i] << " ";
    }
}
void sortBySame(double *a, int num) // Сортировка одинаковых элементов к одинаковым
{
    double example = a[0];
    int last = 0;
    for (int i = 0; i < num; i++) {
        for (int j = last + 1; j < num; j++) {
            if (a[j] - example<0.00001 & a[j] - example> - 0.00001) {
                last++;
                a[j] = a[last];
                a[last] = example;
            }
        }
        last++;
        example = a[last];
    }
}
int numberOfSame(double *a, int num, double example) // подсчёт числа элементов, равных example, в массиве
{
    int res = 0;
    for (int i = 0; i < num; i++) {
        if (a[i] - example<0.00001 & a[i] - example> - 0.00001) {
            res++;
        }
    }
    return res;
}
void replace(double *a, int num, int startOfFirst, int numOfFirst, int numOfSecond)
/* перемена местами двух однородных участков массива, находящихся рядом, где первый
начинается с startOfFirst, а участки содержат numOfFirst, numOfSecond элементов соответственно */
{
    double first = a[startOfFirst];
    double second = a[startOfFirst + numOfFirst];
    for (int i = startOfFirst; i < startOfFirst + numOfSecond; i++) {
        a[i] = second;
    }
    for (int i = startOfFirst + numOfSecond; i < startOfFirst + numOfFirst + numOfSecond; i++) {
        a[i] = first;
    }
}
void sortByNumberOfSame(double *a, int num) // Сортировка массива по частоте встречаемости
{
    sortBySame(a, num);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num;) {
            if (numberOfSame(a, num, a[j]) < numberOfSame(a, num, a[j + numberOfSame(a, num, a[j])])) {
                replace(a, num, j, numberOfSame(a, num, a[j]), numberOfSame(a, num, a[j + numberOfSame(a, num, a[j])]));
            }
            j += numberOfSame(a, num, a[j]);
        }
    }
}
int main()
{
    int numberOfElements;
    std::cout << "How many elements does array have? ";
    std::cin >> numberOfElements;
    double *numbers = new double[numberOfElements];
    Input(numbers, numberOfElements);
    int m = searchForTheBiggest(numbers, numberOfElements, 1);
    std::cout << std::endl
              << numbers[m] << " by number " << m << " is the largest number modulo." << std::endl;
    int start, finish;
    start = searchForMoreThanZero(numbers, numberOfElements, 0);
    if (start != -1) {
        finish = searchForMoreThanZero(numbers, numberOfElements, start + 1);
        if (finish != -1) {
            std::cout << Summa(numbers, numberOfElements, start + 1, finish - 1) << " is the sum of all elements between the first two positives.";
        }
        else {
            std::cout << "Only one positive number among given elements. ";
        }
    }
    else {
        std::cout << "No positive numbers among given elements. ";
    }
    sortByNumberOfSame(numbers, numberOfElements);
    std::cout << std::endl
              << "Sorted array is: ";
    ccout(numbers, numberOfElements);
}
