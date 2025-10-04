#pragma once
#include <thread>
#include "Number.h"
using Num = Number::Number;
class Matrix {
    private:
    Num** numbers;
    int dx, dy;
    Num getPartialMul(const Matrix& other, int i, int j) const;
    Matrix::Matrix() 
    : numbers(nullptr), dx(0), dy(0) {}
    protected:
    Num* getMulLines(const Matrix& other, int j) const;
    public:
    static Num arraySum(const Num* array, int len);
    static Num* arrrayMul(const Num* array, const Num* otherArray, int len);
    int getDX() {return dx;}
    int getDY() {return dy;}
    Matrix::Matrix(Num** given, int rows, int cols)
    : numbers(given), dx(rows), dy(cols) {}
    Matrix(Num** given, unsigned int dx, unsigned int dy);
    Matrix(int dx, int dy);
    Num* operator[] (int index) const {return numbers[index];}
    Matrix operator*(const Matrix& other) const;
    bool isSameSize(const Matrix& other) const;
    Matrix transpond() const;
    void update(int dx, int dy);
    Matrix vanillaMul(const Matrix& other) const;

};