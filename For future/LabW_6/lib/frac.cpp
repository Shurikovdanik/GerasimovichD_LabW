#include "..\headers\basicaction.h"
#include "..\headers\basicclasses.h"
reals::frac reduction (reals::frac given)
{ 
    if ( given.getNumerator() > 0) {
    unsigned int num = given.getNumerator();
    unsigned int denom = given.getDenominator();
    unsigned int gcd = ariphmetics::gcd(num, denom);
    num /= gcd;
    denom /= gcd;
    given.getFrac(num, denom);
    }
    else {
       unsigned int num = -1 * given.getNumerator();
    unsigned int denom = given.getDenominator();
    unsigned int gcd = ariphmetics::gcd(num, denom);
    num /= gcd;
    num *= -1;
    denom /= gcd;  
    given.getFrac(num, denom);
    }
    return given;
}
unsigned int toOneDenom (reals::frac first, reals::frac second) {
    unsigned int denom1 = first.getDenominator();
    unsigned int denom2 = second.getDenominator();
    unsigned int denomCommon = denom1 * denom2 / ariphmetics::gcd(denom1, denom2);
    return denomCommon;
}
