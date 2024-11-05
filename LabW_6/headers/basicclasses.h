#include <iostream>
#pragma once
namespace rationals {
    class frac {
        private:
        int numerator;
        unsigned int denominator;
        public:
        void getFrac (int num,unsigned int denom);
        frac (int num,unsigned int denom) {
           getFrac (num, denom);
        }
        void setNumerator(int given);
        void setDenominator(unsigned int given);
        frac sum (frac summand);
        frac multiply (frac multiplier);
        frac devide (frac devider);
        void output ();
        unsigned int getDenominator();
        int getNumerator();
        frac operator +(frac add);
        frac operator -(const frac decr);
        frac operator * (frac mult);
        frac operator * (int mult);
        frac operator /(frac div);
        bool operator >(frac other);
        bool operator <(frac other);
        bool operator >(int other);
        bool operator <(int other);
    };
    std::ostream& operator << (std::ostream &stream, const frac given);
    void operator >> (std::istream &stream, rationals::frac &given);
}
rationals::frac reduction (rationals::frac given);
unsigned toOneDenom (rationals::frac first, rationals::frac second);
rationals::frac cin();