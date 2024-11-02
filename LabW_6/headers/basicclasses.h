#include <iostream>
#pragma once
namespace reals {
    class frac {
        private:
        int numerator;
        unsigned int denominator;
        public:
        void getFrac (int num,unsigned int denom);
        frac (int num,unsigned int denom) {
           getFrac (num, denom);
        }
        frac sum (frac summand);
        frac multiply (frac multiplier);
        frac devide (frac devider);
        void output ();
        unsigned int getDenominator();
        int getNumerator();
        frac operator +(frac add);
        frac operator * (frac decr);
        frac operator /(frac div);
    };
}
reals::frac reduction (reals::frac given);
unsigned toOneDenom (reals::frac first, reals::frac second);
reals::frac cin();