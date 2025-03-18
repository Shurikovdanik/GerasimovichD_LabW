
#include <iostream>
#include "..\headers\basicclasses.h"
#include "..\headers\basicactions.h"
#include "..\headers\app.h"
int app::main () {
rationals::frac frac1(0, 0), frac2(0, 0);
std::cout << "First frac: " << std::endl;
std::cin >> frac1;
std::cout << std::endl << "Second frac: " << std::endl;
std::cin >> frac2;
std::cout << frac1 << " + " << frac2 << " = "<< (frac1 + frac2) << std::endl;
std::cout << frac1 << " - " << frac2 << " = "<< (frac1 - frac2) << std::endl;
std::cout << frac1 << " * " << frac2 << " = "<< (frac1 * frac2) << std::endl;
std::cout << frac1 << " / " << frac2 << " = "<< (frac1 / frac2) << std::endl;
return 1;
}