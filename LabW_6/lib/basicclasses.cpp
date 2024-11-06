#include <iostream>
#include "..\headers\basicclasses.h"
#include "..\headers\basicactions.h"
 void rationals::frac::getFrac (int num,unsigned int denom)
 {
    numerator = num;
    denominator = denom;
 }
 unsigned int rationals::frac::getDenominator() 
 {
    return denominator;
 }
  int rationals::frac::getNumerator() 
  {
    return numerator;
 }
 void  rationals::frac::setNumerator(int given) {
    numerator = given;
 }
  void  rationals::frac::setDenominator(unsigned int given) {
    denominator = given;
  }
 rationals::frac rationals::frac::sum (rationals::frac summand2)
 {
   rationals::frac summand1 (numerator, denominator);
   unsigned int denomCommon = toOneDenom (summand1, summand2);
   int num1 = numerator * (denomCommon / denominator);
   int num2 = summand2.getNumerator() * denomCommon / summand2.getDenominator();
   rationals::frac summa (num1 + num2, denomCommon);
   return reduction (summa);
 }
 rationals::frac rationals::frac::multiply (rationals::frac multiplier) 
 {
   rationals::frac production (numerator * multiplier.getNumerator(), denominator * multiplier.getDenominator());
   return reduction (production);
 }
 rationals::frac rationals::frac::devide (rationals::frac devider)
 {
   rationals::frac devided (numerator * devider.getDenominator(), denominator * devider.getNumerator());
    return reduction (devided);
 }
 void rationals::frac::output () 
 {
  if (numerator / denominator != 0) {
   std::cout << (int)(numerator / (int)denominator) << " and " <<(int)(numerator % (int)denominator) << "/" << denominator;
  }
  else std::cout << numerator << "/" << denominator;
 }
rationals::frac reduction (rationals::frac given)
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
    rationals::frac temp (given.getNumerator() * (-1), given.getDenominator());
    unsigned int num = temp.getNumerator();
    unsigned int denom = temp.getDenominator();
    unsigned int gcd = ariphmetics::gcd(num, denom);
    num /= gcd;
    denom /= gcd;
    given.getFrac(-num, denom);
    }
    return given;
}

unsigned int toOneDenom (rationals::frac first, rationals::frac second) {
    unsigned int denom1 = first.getDenominator();
    unsigned int denom2 = second.getDenominator();
    unsigned int denomCommon = denom1 * denom2 / ariphmetics::gcd(denom1, denom2);
    return denomCommon;
}
rationals::frac cin () 
{
    int num;
    unsigned int denom;
    std::cout << "Enter frac: ";
    std::cin >> num >> denom;
    rationals::frac res (num, denom);
    std::cout << std::endl;
    return res;
}
rationals::frac rationals::frac::operator +(frac add) {
  rationals::frac temp(numerator, denominator);
  return temp.sum(add);
}
rationals::frac rationals::frac::operator -(frac decr) {
  rationals::frac temp(numerator, denominator);
  if (numerator * decr.getDenominator() - denominator * decr.getNumerator() != 0) {
  return (decr *(-1) + temp);
  }
  else {
    rationals::frac res(0,1);
    return res;
  }
}
rationals::frac rationals::frac:: operator * (frac mult) {
 rationals::frac temp(numerator, denominator);
  return temp.multiply(mult);
}
rationals::frac rationals::frac:: operator * (int mult)  {
  rationals::frac temp(numerator * mult, denominator);
  return  reduction(temp);
}
rationals::frac rationals::frac:: operator /(rationals::frac div) {
 rationals::frac temp(numerator, denominator);
  return temp.devide(div);
}
std::ostream& rationals::operator << (std::ostream &stream, rationals::frac given) {
  if (given.getNumerator() /(int) given.getDenominator() != 0 || given.getNumerator() != 0) {
    if (given.getNumerator() / (int)given.getDenominator() != 0) {
    if (given.getNumerator() % (int)given.getDenominator() != 0) {
   stream << (int)(given.getNumerator() / (int)given.getDenominator()) << " and " << given.getNumerator() % (int)given.getDenominator() << "/" << given.getDenominator();
    }
    else stream <<given.getNumerator() / (int)given.getDenominator();
    }
  else stream << given.getNumerator() << "/" << (int)given.getDenominator();
  }
  else stream << 0;
  return stream;
}
std::istream& rationals::operator >> (std::istream &stream, rationals::frac &given) {
  int num;
  unsigned int denom;
  stream >> num >> denom;
  given.setNumerator(num);
  given.setDenominator(denom);
  return stream;
}
bool rationals::frac::operator >(rationals::frac other) {
  return (numerator * other.getDenominator() > denominator * other.getNumerator());
}
bool rationals::frac::operator <(rationals::frac other) {
  return (numerator * other.getDenominator() > denominator * other.getNumerator());
}
bool rationals::frac::operator >(int other) {
  return (numerator > other * denominator);
}
bool rationals::frac::operator <(int other) {
  return (numerator < other * denominator);
}