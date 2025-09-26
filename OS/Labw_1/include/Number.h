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
        Number(bool sign, long long mantissa, long long exp);
        bool _sign;
        systems _format;
        long long _exp;
        long long _mantissa;

    protected:
        int getExp() const
        {
            return _exp;
        }
        long long getMantissa() const
        {
            return _mantissa;
        }
        Number mulByBasisDegree(int degree)
        {
            this->_exp += degree;
        }

    public:
        Number(float given);
        /**@brief Summarize of two Number elements
         * @param other - Number added
         * @return sum - resulting sum

        */
        Number operator+(const Number &other);
        /**
         * @brief decrease of first arg by second (bin operator)
         * @param other - Number
         * @author Herasimovich D
         */
        Number operator-(const Number &other);
        Number operator*(const Number &other); // Переделать обратные операции. Возможно, по поиску обратного в битах (но это не точно)
        Number operator/(const Number &other);
        std::string toString();
        std::string toDecimalString();
        float toFloat() const;
        Number sqrt() const;
        /**
         * @brief parser from std::string to number
         * @param str - parsed string
         * @param base - systems::base - responsible for numeric system of number
         */
        static Number fromString(const std::string &str, systems base = systems::BASE_TWO)
        {

            bool sign = false;
            size_t start = 0;
            if (!str.empty() && str[0] == '-')
            {
                sign = true;
                start = 1;
            }
            else if (!str.empty() && str[0] == '+')
            {
                start = 1;
            }
            size_t expPos = str.find_first_of("eE^", start);
            std::string mantissaStr = str.substr(start, expPos - start);
            std::string expStr = (expPos != std::string::npos) ? str.substr(expPos + 1) : "0";

            long long mantissa = std::stoll(mantissaStr, nullptr, base);
            long long exp = std::stoll(expStr, nullptr, 10);

            return Number(sign, mantissa, exp);
        }
        long long getMantissa() {return _mantissa;}
        long long getExponenta() {return _exp;}
        int getFormat() {return int(_format);}
        void setFormat(systems sys){this->_format = sys;}
    };

}
