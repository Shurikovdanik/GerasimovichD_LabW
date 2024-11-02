#include <iostream>
#include "headers\basicclasses.h"
#include "headers\basicactions.h"
#include "headers\frac.h"
int main () {
reals::frac frac1 = cin ();
std::cout << std::endl << "Second frac: " << std::endl;
reals::frac frac2 = cin ();
std::cout << "Sum is: ";
(frac1 + frac2).output();
std::cout << ". Production is: ";
(frac1 * frac2).output();
std::cout << ". Devided is: ";
(frac1 / frac2).output();
}