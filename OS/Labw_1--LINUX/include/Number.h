#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>

namespace Numbers {
    enum class systems {
        BASE_TWO = 2,
        BASE_EIGHT = 8,
        BASE_TEN = 10,
        BASE_SIXTEEN = 16
    };

    class Number {
    private:
        bool _sign;
        long long _mantissa;
        long long _exp;
        systems _format;
        
    public:
        Number(float given);
        Number(bool sign, long long mantissa, long long exp, systems base = systems::BASE_TWO);
        
        float toFloat() const;
        std::string toDecimalString() const;
        std::string toString() const;
        Number convertToFormat(systems newFormat) const;
        
        // Arithmetic operators
        Number operator+(const Number &other) const;
        Number operator-(const Number &other) const;
        Number operator*(const Number &other);
        Number operator/(const Number &other);
        
        // Other operations
        Number sqrt() const;
        
        // Accessors
        bool getSign() const { return _sign; }
        long long getMantissa() const { return _mantissa; }
        long long getExp() const { return _exp; }
        systems getFormat() const { return _format; }
        void setFormat(systems fmt) { _format = fmt; }
        
        // Static factory method
        static Number fromString(const std::string &str, systems base = systems::BASE_TEN);
    };
}