#include "../include/Number.h"

float Number::Number::toFloat() const {
    float value = static_cast<float>(_mantissa) * std::pow(10.0f, _exp);
    return _sign ? -value : value;
}
std::string Number::Number::toDecimalString() {
    std::ostringstream oss;

    
    if (_sign) oss << "-";
    else oss << "+";

    
    long double value = static_cast<long double>(_mantissa) * std::pow(10.0L, _exp);

    
    oss << std::fixed << std::setprecision(10) << value;

    return oss.str();
}

std::string Number::Number::toString() {
    std::string result;
    
    result += (_sign ? "-" : "+");

    result += std::to_string(_mantissa);

    result += "e" + std::to_string(_exp);

    return result;
}

namespace Number {
    Number Number::operator *(const Number& other) {
            return Number(0,_mantissa * other.getMantissa(), _exp + other.getExp());
        }
    Number Number::operator /(const Number& other) {
        return Number(0,_mantissa / other.getMantissa(), _exp - other.getExp());
    }
    Number Number::operator +(const Number& other) {
             return Number(0,_mantissa + other.getMantissa(), _exp);
        }
    Number Number::operator -(const Number& other) {
            return Number(0,_mantissa - other.getMantissa(), _exp);
        }
    Number::Number(float given) {
    uint32_t rawBits;
    std::memcpy(&rawBits, &given, sizeof(float));
    std::bitset<32> bits(rawBits);
    this->_sign = bits[31];
    std::bitset<8> expBits;
    for (int i = 0; i < 8; ++i) {
        expBits[i] = bits[i + 23];
    }
    std::bitset<23> manBits;
    for (int i = 0; i < 23; ++i) {
        manBits[i] = bits[i];
    }

    this->_exp = static_cast<int>(expBits.to_ulong()) - 127; 
    this->_mantissa = static_cast<long long>(manBits.to_ulong());

    if (expBits.to_ulong() != 0) {
        this->_mantissa |= (1LL << 23);
    }
    }
    Number::Number (bool sign, long long mantissa, long long exp) {
            this->_sign = sign;
            this->_mantissa = mantissa;
            this->_exp = exp;
        }
    
    Number Number::sqrt() const {
        float original = this->toFloat();
        if (original < 0.0f) {
            throw std::domain_error("Невозможно извлечь корень из отрицательного числа");
        }
        float root = std::sqrt(original);
        return Number(root);
    }

}