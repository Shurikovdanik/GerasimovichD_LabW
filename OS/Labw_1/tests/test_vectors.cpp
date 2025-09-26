#include <gtest/gtest.h>
#include <cmath>
#include <tuple>
#include <vector>
#include "../include/Vector.h"
#include "../include/Number.h"
const double M_PI = 3.14159265358979323846;
using namespace Algebra;

// --- Тест размерности ---
TEST(VectorTest, Dimensions) {
    std::vector<Number::Number> vals = { Number::Number(1.0f), Number::Number(2.0f), Number::Number(3.0f) };
    Vector v(vals);
    EXPECT_EQ(v.dimensions(), 3);
}

// --- Тест доступа к элементам ---
TEST(VectorTest, IndexAccess) {
    std::vector<Number::Number> vals = { Number::Number(1.0f), Number::Number(2.0f) };
    Vector v(vals);
    EXPECT_FLOAT_EQ(v[0].toFloat(), 1.0f);
    EXPECT_FLOAT_EQ(v[1].toFloat(), 2.0f);
}

// --- Евклидова норма ---
TEST(VectorTest, EuclideanNorm) {
    std::vector<Number::Number> vals = { Number::Number(3.0f), Number::Number(4.0f) };
    Vector v(vals);
    EXPECT_NEAR(v.EuclNorma().toFloat(), 5.0f, 1e-6);
}

// --- Скалярное произведение ---
TEST(VectorTest, DotProduct) {
    std::vector<Number::Number> vals1 = { Number::Number(1.0f), Number::Number(2.0f), Number::Number(3.0f) };
    std::vector<Number::Number> vals2 = { Number::Number(4.0f), Number::Number(5.0f), Number::Number(6.0f) };
    Vector v1(vals1);
    Vector v2(vals2);
    EXPECT_FLOAT_EQ(v1.dot(v2).toFloat(), 32.0f); // 1*4 + 2*5 + 3*6
}

// --- Сложение векторов ---
TEST(VectorTest, Addition) {
    std::vector<Number::Number> vals1 = { Number::Number(1.0f), Number::Number(2.0f) };
    std::vector<Number::Number> vals2 = { Number::Number(3.0f), Number::Number(4.0f) };
    Vector v1(vals1);
    Vector v2(vals2);
    Vector sum = v1 + v2;
    EXPECT_FLOAT_EQ(sum[0].toFloat(), 4.0f);
    EXPECT_FLOAT_EQ(sum[1].toFloat(), 6.0f);
}

// --- Вычитание векторов ---
TEST(VectorTest, Subtraction) {
    std::vector<Number::Number> vals1 = { Number::Number(5.0f), Number::Number(7.0f) };
    std::vector<Number::Number> vals2 = { Number::Number(2.0f), Number::Number(3.0f) };
    Vector v1(vals1);
    Vector v2(vals2);
    Vector diff = v1 - v2;
    EXPECT_FLOAT_EQ(diff[0].toFloat(), 3.0f);
    EXPECT_FLOAT_EQ(diff[1].toFloat(), 4.0f);
}

// --- Умножение на скаляр ---
TEST(VectorTest, ScalarMultiplication) {
    std::vector<Number::Number> vals = { Number::Number(1.0f), Number::Number(-2.0f) };
    Vector v(vals);
    Vector scaled = v * Number::Number(3.0f);
    EXPECT_FLOAT_EQ(scaled[0].toFloat(), 3.0f);
    EXPECT_FLOAT_EQ(scaled[1].toFloat(), -6.0f);
}

// --- Полярные координаты ---
TEST(VectorTest, PolarCoordinates) {
    std::vector<Number::Number> vals = { Number::Number(0.0f), Number::Number(1.0f) };
    Vector v(vals);
    auto [r, theta] = v.toPolar();
    EXPECT_NEAR(r, 1.0, 1e-6);
    EXPECT_NEAR(theta, M_PI/2, 1e-6); // угол 90°
}

// --- Сферические координаты ---
TEST(VectorTest, SphericalCoordinates) {
    std::vector<Number::Number> vals = { Number::Number(0.0f), Number::Number(0.0f), Number::Number(1.0f) };
    Vector v(vals);
    auto [r, theta, phi] = v.toSpherical();
    EXPECT_NEAR(r, 1.0, 1e-6);
    EXPECT_NEAR(theta, 0.0, 1e-6);    // азимут
    EXPECT_NEAR(phi, 0.0, 1e-6);      // угол к оси Z
}
