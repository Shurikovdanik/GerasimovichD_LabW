#include <iostream>
#include <ctime>
using namespace std;
bool CHECK_INPUT (double x)
{
 return (x > -1 && x < 1);   
}
bool CHECK_input_paw (int a)
{
    return (a >= 0);
}
double n_paw (double a, int b)
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
    else return -1;
}
int main ()
{
    srand(time(0));
    int k;
    double x;
    float eps;
    std::cout << "x: ";
    std::cin >> x;
    if (CHECK_INPUT ( x))
    {
    std::cout << endl << "k: ";
    std::cin >> k;
    if (CHECK_input_paw) {
    eps = rand () % int(n_paw(10, k / 2)) + 1;
    eps = eps / n_paw(10, 2 * k);
    double part, res;
    res = 0;
    part = 1;
    int i = 2;
    while (part > eps ) {
      
       if (i % 2 == 0)
       res += part;
       else res -= part;
       i++;
       part = part * (i + 1) / (i - 1) * x;

    }
    std::cout << endl << "result is: " << res;
    }
    else std::cout << endl << "Wrong input.";
    }
    else std::cout << endl << "Wrong input.";

}