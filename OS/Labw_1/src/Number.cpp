#include "../include/Number.h"

float Number::Number::toFloat() const
{
    float value = static_cast<float>(_mantissa) * std::pow(int(this->_format), _exp);
    return _sign ? -value : value;
}
std::string Number::Number::toDecimalString()
{
    std::ostringstream oss;

    if (_sign)
        oss << "-";
    else
        oss << "";

    long double value = static_cast<long double>(_mantissa) * std::pow(int(this->_format), _exp);

    oss << std::fixed << std::setprecision(10) << value;

    return oss.str();
}

std::string Number::Number::toString()
{
    std::string result;

    result += (_sign ? "-" : "");

    result += std::to_string(_mantissa);

    result += "e" + std::to_string(_exp);

    return result;
}

namespace Number
{
    Number Number::operator+(const Number &other)
    {
        long long mantA = _mantissa;
        long long mantB = other._mantissa;
        long long expA = _exp;
        long long expB = other._exp;
        if (expA > expB)
        {
            mantB >>= (expA - expB);
            expB = expA;
        }
        else if (expB > expA)
        {
            mantA >>= (expB - expA);
            expA = expB;
        }
        long long mantRes;
        bool signRes = _sign;

        if (_sign == other._sign)
        {
            mantRes = mantA + mantB;
        }
        else
        {
            mantRes = mantA - mantB;
            if (mantRes < 0)
            {
                mantRes = -mantRes;
                signRes = !_sign;
            }
        }

        while (mantRes >= (1 << 16))
        {
            mantRes >>= 1;
            expA++;
        }
        while (mantRes > 0 && mantRes < (1 << 15))
        {
            mantRes <<= 1;
            expA--;
        }

        return Number(signRes, mantRes, expA);
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
        return Number(0, _mantissa / other.getMantissa(), _exp - other.getExp());
    }

    Number Number::operator-(const Number &other)
    {
        return Number(0, _mantissa - other.getMantissa(), _exp);
    }

    Number::Number(float given) {
        uint32_t rawBits;
        std::memcpy(&rawBits, &given, sizeof(float));
        this->_sign = (rawBits >> 31) & 0x1;
        uint32_t expBits = (rawBits >> 23) & 0xFF;
        uint32_t manBits = rawBits & 0x7FFFFF;
        this->_exp = static_cast<int>(expBits) - 127;
        if (expBits != 0) {
            this->_mantissa = static_cast<long long>(manBits) | (1LL << 23);
        } else {
            this->_mantissa = static_cast<long long>(manBits);
        }
        this->_format = BASE_TWO;
    }
    Number::Number(bool sign, long long mantissa, long long exp)
    {
        this->_sign = sign;
        this->_mantissa = mantissa;
        this->_exp = exp;
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

}