#pragma once
#include <iostream>
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
    };
}