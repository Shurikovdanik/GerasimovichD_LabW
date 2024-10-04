#include <iostream>
#include "..\headers\frac.h"
#include "..\headers\basicclasses.h"
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
   int num1 = numerator * denomCommon / denominator;
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
