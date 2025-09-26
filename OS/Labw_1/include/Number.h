#pragma once

#include <bitset>
#include <climits>
#include <sstream>
#include <iomanip>
#include <string>

template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

namespace Number
{
    enum systems
    {
        BASE_TWO = 2,
        BASE_FOUR = 4,
        BASE_TEN = 10,
        BASE_SIXTEEN = 16
    };
    const short FLOAT_MANTISSA = 8;
    // Class number is on Mantissa (16 bite), exponenta (8 bite). _format is responsible for IOutput
    class Number
    {
    private:
        Number(bool sign, long long mantissa, long long exp, systems base = systems::BASE_TEN);
        bool _sign;
        systems _format;
        long long _exp;
        long long _mantissa;

    protected:
        int getExp() const
        {
            return _exp;
        }
        Number mulByBasisDegree(int degree)
        {
            this->_exp += degree;
        }

    public:
        long long getMantissa() const
        {
            return _mantissa;
        }
        Number(float given);
        Number convertToFormat(systems newFormat) const;
        /**@brief Summarize of two Number elements
         * @param other - Number added
         * @return sum - resulting sum

        */
        Number operator+(const Number &other) const;
        /**
         * @brief decrease of first arg by second (bin operator)
         * @param other - Number
         * @author Herasimovich D
         */
        Number operator-(const Number &other) const;
        Number operator*(const Number &other); 
        Number operator/(const Number &other);
        std::string toString() const;
        std::string toDecimalString() const;
        float toFloat() const;
        Number sqrt() const;
        /**
         * @brief parser from std::string to number
         * @param str - parsed string
         * @param base - systems::base - responsible for numeric system of number
         */
        static Number fromString(const std::string &str, systems base);
        long long getExponenta() { return _exp; }
        int getFormat() { return int(_format); }
        void setFormat(systems sys) { this->_format = sys; }
    };

}
