#include <iostream>
#include "headers\basicclasses.h"
#include "headers\basicactions.h"
#include "headers\frac.h"
reals::frac cin();
int main () {
reals::frac frac1 = cin ();
std::cout << std::endl << "Second frac: " << std::endl;
reals::frac frac2 = cin ();
std::cout << "Sum is: ";
frac1.sum(frac2).output();
std::cout << ". Production is: ";
frac1.multiply(frac2).output();
std::cout << ". Devided is: ";
frac1.devide(frac2).output();
}
reals::frac cin () 
{
    int num;
    unsigned int denom;
    std::cout << "Enter frac: ";
    std::cin >> num >> denom;
    reals::frac res (num, denom);
    std::cout << std::endl;
    return res;
}