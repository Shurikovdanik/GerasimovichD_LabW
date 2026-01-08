#pragma once
#include <thread>
#include "Number.h"
using Num = float;
const int BLOCK_SIZE = 64;
class Matrix
{
private:
    float **numbers;
    int dx, dy;
    Num getPartialMul(const Matrix &other, int i, int j) const;

protected:
    Num *getMulLines(const Matrix &other, int j) const;

public:
    Matrix() : numbers(nullptr), dx(0), dy(0) {}
    static Num arraySum(const Num *array, int len);
    static Num *arrrayMul(const Num *array, const Num *otherArray, int len);
    int getDX() const{ return dx; }
    int getDY() const{ return dy; }
    Matrix(float **given, int rows, int cols)
        : numbers(given), dx(rows), dy(cols) {}
    Matrix(Num **given, unsigned int dx, unsigned int dy);
    Matrix(int dx, int dy);
    float *operator[](int index) const { return numbers[index]; }
    Matrix operator*(const Matrix &other) const;
    bool isSameSize(const Matrix &other) const;
    Matrix transpond() const;
    void update(int dx, int dy);
    Matrix vanillaMul(const Matrix &other) const;
    Matrix multiplyWithoutChannel(const Matrix &other) const;
    std::string toString() const;
};