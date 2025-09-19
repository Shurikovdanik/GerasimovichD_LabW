#pragma once

#include <bitset>
#include <climits>
#include <sstream>
#include <iomanip>
#include <string>

template <typename T>
std::string to_string(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
namespace Number {
    enum systems {
        BASE_TWO = 2,
        BASE_FOUR = 4,
        BASE_SIXTEEN = 16
    };
    const short FLOAT_MANTISSA = 8;
    //Class number is on Mantissa (16 bite), exponenta (8 bite)
    class Number {
        private:
        Number (bool sign, long long mantissa, long long exp);
        bool _sign;
        systems _format;
        long long _exp;
        long long _mantissa;
        protected:
        int getExp() const{
            return _exp;
        }
        long long getMantissa() const{
            return _mantissa;
        } 
        public:
        Number(float given);
    /**@brief Summarize of two Number elements
     * @param other - Number added
     * @return sum - resulting sum
     
    */
Number operator +(const Number& other);
Number operator -(const Number& other);
Number operator *(const Number& other);
Number operator /(const Number& other);
std::string toString();
std::string toDecimalString();
float toFloat() const;
Number sqrt() const;

    };

}