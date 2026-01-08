#include "../include/Number.h"
#include <iostream>

float Number::Number::toFloat() const {
    long double m = static_cast<long double>(_mantissa) / (1LL << 23);
    long double value = m * std::pow(2.0L, _exp); 
    return _sign ? -static_cast<float>(value) : static_cast<float>(value);
}



std::string Number::Number::toDecimalString() const {
    std::ostringstream oss;
    if (_sign) oss << "-";
    long double m = static_cast<long double>(_mantissa) / (1LL << 23);
    long double value = m * std::pow(2.0L, _exp);
    oss << std::fixed << std::setprecision(10) << value;
    return oss.str();
}



std::string Number::Number::toString() const
{
    std::ostringstream oss;

    if (_sign)
        oss << "-";

    oss << _mantissa << " * "
        << static_cast<int>(_format)
        << "^" << _exp;

    return oss.str();
}

Number::Number Number::Number::convertToFormat(systems newFormat) const
{
    if (newFormat == _format) {
        return *this;
    }
    if (_mantissa == 0) {
        return Number(false, 0, 0, newFormat);
    }

    bool sign = _sign;

    long double m = static_cast<long double>(_mantissa) / (1LL << 23); 
    long double value = m * std::pow(static_cast<long double>(_format), _exp);

    if (sign) value = -value;
    if (value < 0) value = -value; 

  
    long long mantissa = 0;
    long long exp = 0;

    if (newFormat == systems::BASE_TWO)
    {
        int e;
        long double frac = std::frexp(value, &e);
        frac *= 2.0;                              
        e -= 1;

        mantissa = static_cast<long long>(frac * (1LL << 23));
        exp = e - 23;
    }
    else
    {
        long double base = static_cast<long double>(newFormat);
        exp = static_cast<long long>(std::floor(std::log(value) / std::log(base)));
        long double frac = value / std::pow(base, exp);

        mantissa = static_cast<long long>(frac * (1LL << 23));
        exp -= 23;
    }

    return Number(sign, mantissa, exp, newFormat);
}



namespace Number
{
    
   /*Number Number::operator+(const Number &other) const
{
    Number temp = other;
    temp.setFormat(this->_format);

    // Восстанавливаем оба числа
    auto toLongDouble = [](const Number &n) {
        long double m = static_cast<long double>(n._mantissa) / (1LL << 23);
        long double v = m * std::pow(2.0L, n._exp);
        return n._sign ? -v : v;
    };

    long double valA = toLongDouble(*this);
    long double valB = toLongDouble(temp);

    long double sum = valA + valB;

    if (sum == 0.0L) {
        return Number(false, 0, 0, _format);
    }

    bool signRes = sum < 0;
    if (signRes) sum = -sum;

    // Нормализация Q23
    int expRes = 0;
    if (sum > 0.0L) {
        while (sum >= 2.0L) {
            sum /= 2.0L;
            expRes++;
        }
        while (sum < 1.0L) {
            sum *= 2.0L;
            expRes--;
        }
    }
    long long mantRes = static_cast<long long>(sum * (1LL << 23));
    return Number(signRes, mantRes, expRes, _format);
}






    Number Number::operator*(const Number &other)
    {
        long long mantRes = (_mantissa * other._mantissa) >> 16;
        long long expRes = _exp + other._exp;
        bool signRes = _sign ^ other._sign;

        while (mantRes >= (1 << 16))
        {
            mantRes >>= 1;
            expRes++;
        }
        while (mantRes > 0 && mantRes < (1 << 15))
        {
            mantRes <<= 1;
            expRes--;
        }

        return Number(signRes, mantRes, expRes);
    }
    Number Number::operator/(const Number &other)
    {
        // Calculate sign
        bool signRes = _sign ^ other._sign;
        // Convert to long double
        long double a = static_cast<long double>(_mantissa) / (1LL << 23);
        long double b = static_cast<long double>(other.getMantissa()) / (1LL << 23);
        long double valA = a * std::pow(2.0L, _exp);
        long double valB = b * std::pow(2.0L, other.getExp());
        if (_sign) valA = -valA;
        if (other._sign) valB = -valB;
        // Handle division by zero
        if (valB == 0.0L) {
            throw std::domain_error("Division by zero");
        }
        // Handle zero numerator
        if (valA == 0.0L) {
            return Number(false, 0, 0, _format);
        }
        long double result = valA / valB;
        if (result < 0) result = -result;
        // Normalize to Q23
        int expRes = 0;
        if (result > 0.0L) {
            while (result >= 2.0L) {
                result /= 2.0L;
                expRes++;
            }
            while (result < 1.0L) {
                result *= 2.0L;
                expRes--;
            }
        }
        long long mantRes = static_cast<long long>(result * (1LL << 23));
        return Number(signRes, mantRes, expRes, _format);
    }

    Number Number::operator-(const Number &other) const
    {
        Number temp = other;
        temp._sign = !(temp._sign);
        return *this + temp;
    }
*/
Number Number::operator+(const Number &other) const
{
    Number temp = other;
    temp.setFormat(this->_format); 

    auto toLongDouble = [](const Number &n) {
        long double m = static_cast<long double>(n._mantissa) / (1LL << 23);
        long double v = m * std::pow(2.0L, n._exp);
        return n._sign ? -v : v;
    };

    long double valA = toLongDouble(*this);
    long double valB = toLongDouble(temp);

    long double sum = valA + valB;

    if (sum == 0.0L) {
        return Number(false, 0, 0, _format);
    }

    bool signRes = sum < 0;
    if (signRes) sum = -sum;

    int expRes = 0;
    if (sum > 0.0L) {
        while (sum >= 2.0L) {
            sum /= 2.0L;
            expRes++;
        }
        while (sum < 1.0L) {
            sum *= 2.0L;
            expRes--;
        }
    }
    long long mantRes = static_cast<long long>(sum * (1LL << 23));
    if (mantRes != 0) {
        while (mantRes < (1LL << 23)) {
            mantRes <<= 1;
            expRes--;
        }
        while (mantRes >= (2LL << 23)) {
            mantRes >>= 1;
            expRes++;
        }
    }
    return Number(signRes, mantRes, expRes, _format);
}

Number Number::operator*(const Number &other)
{
    long long mantRes = (_mantissa * other._mantissa) >> 23;
    long long expRes = _exp + other._exp;
    bool signRes = _sign ^ other._sign;

    if (mantRes != 0) {
        while (mantRes < (1LL << 23)) {
            mantRes <<= 1;
            expRes--;
        }
        while (mantRes >= (2LL << 23)) {
            mantRes >>= 1;
            expRes++;
        }
    }

    return Number(signRes, mantRes, expRes, _format);
}

Number Number::operator/(const Number &other)
{
    bool signRes = _sign ^ other._sign;
    long double a = static_cast<long double>(_mantissa) / (1LL << 23);
    long double b = static_cast<long double>(other.getMantissa()) / (1LL << 23);
    long double valA = a * std::pow(2.0L, _exp);
    long double valB = b * std::pow(2.0L, other.getExp());
    if (_sign) valA = -valA;
    if (other._sign) valB = -valB;
    if (valB == 0.0L) {
        throw std::domain_error("Division by zero");
    }
    if (valA == 0.0L) {
        return Number(false, 0, 0, _format);
    }
    long double result = valA / valB;
    if (result < 0) result = -result;
    int expRes = 0;
    if (result > 0.0L) {
        while (result >= 2.0L) {
            result /= 2.0L;
            expRes++;
        }
        while (result < 1.0L) {
            result *= 2.0L;
            expRes--;
        }
    }
    long long mantRes = static_cast<long long>(result * (1LL << 23));
    return Number(signRes, mantRes, expRes, _format);
}
Number Number::operator-(const Number &other) const
{
    Number temp = other;
    temp._sign = !(temp._sign);
    return *this + temp;
}
    Number::Number(float given)
{
    uint32_t rawBits;
    std::memcpy(&rawBits, &given, sizeof(float));

    this->_sign = (rawBits >> 31) & 0x1;
    uint32_t expBits = (rawBits >> 23) & 0xFF;
    uint32_t manBits = rawBits & 0x7FFFFF;

    if (expBits == 0)
    {
        this->_exp = -126;
        this->_mantissa = static_cast<long long>(manBits);
        if (manBits != 0)
        {
            while ((this->_mantissa & (1 << 23)) == 0)
            {
                this->_mantissa <<= 1;
                this->_exp--;
            }
        }
    }
    else if (expBits == 255)
    {
        this->_exp = INT_MAX;
        this->_mantissa = manBits;
    }
    else
    {
        this->_exp = static_cast<int>(expBits) - 127;
        this->_mantissa = static_cast<long long>(manBits) | (1LL << 23);
    }

    this->_format = systems::BASE_TWO;
}


    Number::Number(bool sign, long long mantissa, long long exp, systems base)
    {
        this->_sign = sign;
        this->_mantissa = mantissa;
        this->_exp = exp;
        this->_format = base;
    }

    Number Number::sqrt() const
    {
        float original = this->toFloat();
        if (original < 0.0f)
        {
            throw std::domain_error("Невозможно извлечь корень из отрицательного числа");
        }
        float root = std::sqrt(original);
        return Number(root);
    }
    Number Number::fromString(const std::string &str, systems base)
    {
        bool sign = false;
        size_t pos = 0;

        if (str[pos] == '-')
        {
            sign = true;
            pos++;
        }
        else if (str[pos] == '+')
        {
            pos++;
        }

        size_t dotPos = str.find('.', pos);
        size_t ePos = str.find_first_of("eE", pos);

        std::string intPart = (dotPos != std::string::npos) ? str.substr(pos, dotPos - pos) : str.substr(pos, ePos - pos);
        std::string fracPart = (dotPos != std::string::npos && ePos != std::string::npos) ? str.substr(dotPos + 1, ePos - dotPos - 1) :
                               (dotPos != std::string::npos) ? str.substr(dotPos + 1) : "";
        std::string expPart = (ePos != std::string::npos) ? str.substr(ePos + 1) : "0";

        long long intValue = 0;
        for (char c : intPart)
        {
            intValue = intValue * static_cast<int>(base) + (isdigit(c) ? c - '0' : tolower(c) - 'a' + 10);
        }

        long long fracValue = 0;
        long long fracDivisor = 1;
        for (char c : fracPart)
        {
            fracValue = fracValue * static_cast<int>(base) + (isdigit(c) ? c - '0' : tolower(c) - 'a' + 10);
            fracDivisor *= static_cast<int>(base);
        }

        int expValue = std::stoi(expPart);

        long double value = static_cast<long double>(intValue) + static_cast<long double>(fracValue) / fracDivisor;
        value *= std::pow(static_cast<long double>(base), expValue);
        if (sign) value = -value;

        if (value == 0.0L) {
            return Number(false, 0, 0, base);
        }

        bool signRes = value < 0;
        if (signRes) value = -value;

        int expRes = 0;
        if (value > 0.0L) {
            while (value >= 2.0L) {
                value /= 2.0L;
                expRes++;
            }
            while (value < 1.0L) {
                value *= 2.0L;
                expRes--;
            }
        }
        return Number(signRes, static_cast<long long>(value * (1LL << 23)), expRes, base);
    }
}