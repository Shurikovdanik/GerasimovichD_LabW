#include <iostream>
#include "..\headers\basicclasses.h"
#include "..\headers\basicactions.h"
 void reals::frac::getFrac (int num,unsigned int denom)
 {
    numerator = num;
    denominator = denom;
 }
 unsigned int reals::frac::getDenominator() 
 {
    return denominator;
 }
  int reals::frac::getNumerator() 
  {
    return numerator;
 }
 reals::frac reals::frac::sum (reals::frac summand2)
 {
   reals::frac summand1 (numerator, denominator);
   unsigned int denomCommon = toOneDenom (summand1, summand2);
   int num1 = numerator * (denomCommon / denominator);
   int num2 = summand2.getNumerator() * denomCommon / summand2.getDenominator();
   reals::frac summa (num1 + num2, denomCommon);
   return reduction (summa);
 }
 reals::frac reals::frac::multiply (reals::frac multiplier) 
 {
   reals::frac production (numerator * multiplier.getNumerator(), denominator * multiplier.getDenominator());
   return reduction (production);
 }
 reals::frac reals::frac::devide (reals::frac devider)
 {
   reals::frac devided (numerator * devider.getDenominator(), denominator * devider.getNumerator());
    return reduction (devided);
 }
 void reals::frac::output () 
 {
   std::cout << numerator << "/" << denominator;
 }
reals::frac reduction (reals::frac given)
{
    
    if ( given.getNumerator() > 0) {
    unsigned int num = (unsigned int)given.getNumerator();
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