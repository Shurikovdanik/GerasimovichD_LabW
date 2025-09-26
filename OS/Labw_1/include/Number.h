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
        Number mulByBasisDegree(int degree) {
            this->_exp += degree;
        }
        public:
        Number(float given); //Нужно покопаться в реализации float и понять как извлечь без последствий биты(тут что-то не так)
    /**@brief Summarize of two Number elements
     * @param other - Number added
     * @return sum - resulting sum
     
    */
Number operator +(const Number& other);
/**
 * @brief decrease of first arg by second (bin operator)
 * @param other - Number
 * @author Herasimovich D
 */
Number operator -(const Number& other);
Number operator *(const Number& other); //Переделать обратные операции. Возможно, по поиску обратного в битах (но это не точно)
Number operator /(const Number& other);
std::string toString();
std::string toDecimalString();
float toFloat() const;
Number sqrt() const;

Number fromString(const std::string& inboundString) { // переделать
    
    this->_sign = 1;
    this->_exp = 0;
    this->_mantissa = 0;

    size_t i = 0;

    // 1. Знак
    if (inboundString[i] == '+') {
        i++;
    } else if (inboundString[i] == '-') {
        this->_sign = -1;
        i++;
    }

    // 2. Цифры до точки
    bool hasDigits = false;
    while (i < inboundString.size() && std::isdigit(inboundString[i])) {
        this->_mantissa.push_back(inboundString[i]);
        hasDigits = true;
        i++;
    }

    // 3. Десятичная точка
    if (i < inboundString.size() && inboundString[i] == '.') {
        i++;
        while (i < inboundString.size() && std::isdigit(inboundString[i])) {
            result.mantissa.push_back(inboundString[i]);
            result.exponent--; // каждая цифра после точки уменьшает экспоненту
            hasDigits = true;
            i++;
        }
    }

    if (!hasDigits) {
        throw std::invalid_argument("Invalid number: no digits");
    }

    // 4. Экспонента (e/E)
    if (i < inboundString.size() && (inboundString[i] == 'e' || inboundString[i] == 'E')) {
        i++;
        int expSign = 1;
        if (i < inboundString.size() && (inboundString[i] == '+' || inboundString[i] == '-')) {
            if (inboundString[i] == '-') expSign = -1;
            i++;
        }

        int expValue = 0;
        bool hasExpDigits = false;
        while (i < inboundString.size() && std::isdigit(inboundString[i])) {
            expValue = expValue * 10 + (inboundString[i] - '0');
            hasExpDigits = true;
            i++;
        }
        if (!hasExpDigits) {
            throw std::invalid_argument("Invalid number: bad exponent");
        }
        result.exponent += expSign * expValue;
    }

    // 5. Удаляем ведущие нули в мантиссе
    size_t pos = result.mantissa.find_first_not_of('0');
    if (pos == std::string::npos) {
        result.mantissa = "0";
        result.exponent = 0;
        result.sign = 1; // ноль всегда положительный
    } else {
        result.mantissa.erase(0, pos);
    }

    return result;
}

    };

}
