#include <gtest/gtest.h>
#include "../include/Number.h"

TEST(ToStringTest, IntConversion) {
    EXPECT_EQ(to_string(42), "42");
}

TEST(ToStringTest, FloatConversion) {
    EXPECT_EQ(to_string(3.14f), "3.14");
}

TEST(NumberTest, CanBeConstructedFromFloat) {
    Number::Number n(3.14f);
    SUCCEED();
}



TEST(NumberOperatorsTest, Addition) {
    Number::Number a(2.5f);
    Number::Number b(3.5f);
    Number::Number result = a + b;
    EXPECT_FLOAT_EQ(result.toFloat(), 6.0f);
}

TEST(NumberOperatorsTest, Subtraction) {
    Number::Number a(10.0f);
    Number::Number b(4.0f);
    Number::Number result = a - b;
    EXPECT_FLOAT_EQ(result.toFloat(), 6.0f);
}

TEST(NumberOperatorsTest, Multiplication) {
    Number::Number a(2.0f);
    Number::Number b(5.0f);
    Number::Number result = a * b;
    EXPECT_FLOAT_EQ(result.toFloat(), 10.0f);
}

TEST(NumberOperatorsTest, Division) {
    Number::Number a(9.0f);
    Number::Number b(3.0f);
    Number::Number result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), 3.0f);
}

TEST(NumberOperatorsTest, DivisionByOne) {
    Number::Number a(7.0f);
    Number::Number b(1.0f);
    Number::Number result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), 7.0f);
}

TEST(NumberOperatorsTest, NegativeNumbers) {
    Number::Number a(-4.0f);
    Number::Number b(2.0f);
    Number::Number result = a + b;
    EXPECT_FLOAT_EQ(result.toFloat(), -2.0f);

    result = a - b;
    EXPECT_FLOAT_EQ(result.toFloat(), -6.0f);

    result = a * b;
    EXPECT_FLOAT_EQ(result.toFloat(), -8.0f);

    result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), -2.0f);
}