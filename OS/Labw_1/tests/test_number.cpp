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



TEST(NumberAdditionTest, SimplePositive)
{
     Number::Number a =  Number::Number::fromString("1.0e0", Number::systems::BASE_TEN);
     Number::Number b =  Number::Number::fromString("1.0e0", Number::systems::BASE_TEN);
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
}
TEST(NumberAdditionTest, SimplePositiveFromFloat)
{
     Number::Number a =  Number::Number(1.0f);
     Number::Number b =  Number::Number(1.0f);
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
}

TEST(NumberAdditionTest, Fractional)
{
     Number::Number a =  Number::Number::fromString("1.5e0", Number::systems::BASE_TEN);
     Number::Number b =  Number::Number::fromString("1.5e0", Number::systems::BASE_TEN);
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 3.0f);
}

TEST(NumberAdditionTest, DifferentSigns)
{
     Number::Number a =  Number::Number::fromString("2.0e0", Number::systems::BASE_TEN);
     Number::Number b =  Number::Number::fromString("-1.0e0", Number::systems::BASE_TEN);
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 1.0f);
}

TEST(NumberAdditionTest, DifferentExponents)
{
     Number::Number a =  Number::Number::fromString("1.0e3", Number::systems::BASE_TEN); 
     Number::Number b =  Number::Number::fromString("1.0e2", Number::systems::BASE_TEN); 
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 1100.0f);
}

TEST(NumberAdditionTest, NormalizationOverflow)
{
    // 1.0 * 2^0 + 1.0 * 2^0 = 2.0
     Number::Number a =  Number::Number::fromString("1.0e0", Number::systems::BASE_TEN);
     Number::Number b =  Number::Number::fromString("1.0e0", Number::systems::BASE_TEN);
     Number::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
    // Проверим, что мантисса нормализована в Q23
    EXPECT_GE(c.getMantissa(), (1 << 23));
    EXPECT_LT(c.getMantissa(), (1 << 24));
}
TEST(NumberOperatorsTest, Subtraction) {
    Number::Number a(10.0f);
    Number::Number b(4.0f);
    Number::Number result = a - b;
    EXPECT_FLOAT_EQ(result.toFloat(), 6.0f);
}

TEST(NumberOperatorsTest, MultiplicationSimple) {
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