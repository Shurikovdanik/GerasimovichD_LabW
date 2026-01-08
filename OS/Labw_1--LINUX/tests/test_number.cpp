#include <gtest/gtest.h>
#include "../include/Number.h"



TEST(NumberTest, CanBeConstructedFromFloat) {
    Numbers::Number n(3.14f);
    SUCCEED();
}



TEST(NumberAdditionTest, SimplePositive)
{
     Numbers::Number a =  Numbers::Number::fromString("1.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number b =  Numbers::Number::fromString("1.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
}
TEST(NumberAdditionTest, SimplePositiveFromFloat)
{
     Numbers::Number a =  Numbers::Number(1.0f);
     Numbers::Number b =  Numbers::Number(1.0f);
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
}

TEST(NumberAdditionTest, Fractional)
{
     Numbers::Number a =  Numbers::Number::fromString("1.5e0", Numbers::systems::BASE_TEN);
     Numbers::Number b =  Numbers::Number::fromString("1.5e0", Numbers::systems::BASE_TEN);
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 3.0f);
}

TEST(NumberAdditionTest, DifferentSigns)
{
     Numbers::Number a =  Numbers::Number::fromString("2.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number b =  Numbers::Number::fromString("-1.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 1.0f);
}

TEST(NumberAdditionTest, DifferentExponents)
{
     Numbers::Number a =  Numbers::Number::fromString("1.0e3", Numbers::systems::BASE_TEN); 
     Numbers::Number b =  Numbers::Number::fromString("1.0e2", Numbers::systems::BASE_TEN); 
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 1100.0f);
}

TEST(NumberAdditionTest, NormalizationOverflow)
{
    // 1.0 * 2^0 + 1.0 * 2^0 = 2.0
     Numbers::Number a =  Numbers::Number::fromString("1.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number b =  Numbers::Number::fromString("1.0e0", Numbers::systems::BASE_TEN);
     Numbers::Number c = a + b;

    EXPECT_FLOAT_EQ(c.toFloat(), 2.0f);
    // Проверим, что мантисса нормализована в Q23
    EXPECT_GE(c.getMantissa(), (1 << 23));
    EXPECT_LT(c.getMantissa(), (1 << 24));
}
TEST(NumberOperatorsTest, Subtraction) {
    Numbers::Number a(10.0f);
    Numbers::Number b(4.0f);
    Numbers::Number result = a - b;
    EXPECT_FLOAT_EQ(result.toFloat(), 6.0f);
}

TEST(NumberOperatorsTest, MultiplicationSimple) {
    Numbers::Number a(2.0f);
    Numbers::Number b(5.0f);
    Numbers::Number result = a * b;
    EXPECT_FLOAT_EQ(result.toFloat(), 10.0f);
}

TEST(NumberOperatorsTest, Division) {
    Numbers::Number a(9.0f);
    Numbers::Number b(3.0f);
    Numbers::Number result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), 3.0f);
}

TEST(NumberOperatorsTest, DivisionByOne) {
    Numbers::Number a(7.0f);
    Numbers::Number b(1.0f);
    Numbers::Number result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), 7.0f);
}

TEST(NumberOperatorsTest, NegativeNumbers) {
    Numbers::Number a(-4.0f);
    Numbers::Number b(2.0f);
    Numbers::Number result = a + b;
    EXPECT_FLOAT_EQ(result.toFloat(), -2.0f);

    result = a - b;
    EXPECT_FLOAT_EQ(result.toFloat(), -6.0f);

    result = a * b;
    EXPECT_FLOAT_EQ(result.toFloat(), -8.0f);

    result = a / b;
    EXPECT_FLOAT_EQ(result.toFloat(), -2.0f);
}