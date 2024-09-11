#include <iostream>
#include <ctime>
using namespace std;
bool CHECK_INPUT (double x)
{
 return (x > -1 && x < 1);   
}
double n_paw (double a, int b)
{
    if (b != 0)
    {
    long long res = a;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
    }
    else return 1;
}
int main ()
{
    srand(time(0));
    int k;
    double x;
    float eps;
    cout << "x: ";
    cin >> x;
    if (CHECK_INPUT ( x))
    {
    cout << endl << "k: ";
    cin >> k;
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
    cout << endl << "result is: " << res;
    }
    else cout << endl << "Wrong input.";

}