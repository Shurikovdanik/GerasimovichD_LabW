#include <iostream>
#include <ctime>
double mod(double a) //          |a|
{
    if (a < 0)
    {
        a -= 2 * a;
    }
    return a;
}
bool CHECK_INPUT(double x) // проверка аргумента функции на принадлежность области определения
{
    return (x > -1 && x < 1);
}
bool CHECK_input_paw(int a) // проверка натуральности + {0} числа
{
    return (a >= 0);
}
double n_paw(double a, int b) // возведение в натуральную + {0} степень
{
    if (b > 0)
    {
        long long res = a;
        for (int i = 0; i < b; i++)
        {
            res *= a;
        }
        return res;
    }
    else if (b == 0)
    {
        return 1;
    }
    else
        return -1;
}
int main()
{
    srand(time(0));
    int k;
    double x;
    float eps;
    std::cout << "1/(1 + x)^3" << std::endl;
    std::cout << "x: ";
    std::cin >> x; // Ввод. x - аргумент функции. 10^k - ограничивает приближение сверху.
    if (CHECK_INPUT(x))
    {
        std::cout << std::endl
                  << "k: ";
        std::cin >> k;
        if (CHECK_input_paw(k))
        {
            eps = rand() % int(n_paw(10, k / 2)) + 1;
            eps = eps / n_paw(10, 2 * k);
            double part, res;
            res = 0;   // конечный результат
            part = 1;  // текущее слагаемое. 1-ое слагаемое = 1
            int i = 2; // счётчик слагаемых. Первым изменением будет переход ко 2-ому слагаемому
            while (mod(part) > eps)
            { // пока часть по модулю не станет меньше ограничения,к конечному результату прибавляется слагаемое, которое затем изменяется

                if (i % 2 == 0)
                    res += part;
                else
                    res -= part;
                part = part * (i + 1) / (i - 1) * x;
                i++;
            }
            std::cout << std::endl
                      << "result is: " << res; // вывод
        }
        else
            std::cout << std::endl
                      << "Wrong input.";
    }
    else
        std::cout << std::endl
                  << "Wrong input.";
}