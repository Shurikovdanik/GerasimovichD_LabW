#include "..\headers\basicaction.h"
#include "..\headers\basicclasses.h"
reals::frac reduction (reals::frac given)
{
    unsigned int num = given.getNumerator();
    unsigned int denom = given.getDenominator();
    unsigned int gcd = ariphmetics::gcd(num, denom);
    num /= gcd;
    denom /= gcd;
    given.getFrac(num, denom);
    return given;
}
unsigned int toOneDenom (reals::frac first, reals::frac second) {
    unsigned int denom1 = first.getDenominator();
    unsigned int denom2 = second.getDenominator();
    unsigned int denomCommon = denom1 * denom2 / ariphmetics::gcd(denom1, denom2);
    return denomCommon;
}