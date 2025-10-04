#include "../include/Matrix.h"
#include "../include/Number.h"
#include <vector>
#include <stdexcept>
#include <iostream>
using Num = Number::Number;
// Конструкторы (упрощённо)
Matrix::Matrix(Num** given, unsigned int dx,unsigned int dy)
    : numbers(given)
{
    //TODO: measures   
    dx = dx;
    dy = dy;
}
void Matrix::update(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
}

bool Matrix::isSameSize(const Matrix& other) const {
    return (this->dx == other.dx && this->dy == other.dy);
}

Matrix Matrix::transpond() const {
    Num** res = new Num* [dx];
    for (int i = 0; i < dy; i++) {
        res[i] = new Num[dx];
        for (int j = 0; j < dx; j++) {
            res[i][j] = numbers[j][i];
        }
    }
    return Matrix(res, dy, dx);
}


// Вспомогательная функция для вычисления одного элемента
Num Matrix::getPartialMul(const Matrix& other, int i, int j) const {
    Num sum = 0;
    for (int k = 0; k < dx; ++k) {
        sum = sum + (this->numbers[i][k] * other.numbers[k][j]);
    }
    return sum;
}

// Вспомогательная функция для вычисления строки
Num* Matrix::getMulLines(const Matrix& other, int i) const {
    Num* row = new Num[other.dx];
    for (int j = 0; j < other.dx; ++j) {
        row[j] = getPartialMul(other, i, j);
    }
    return row;
}
Matrix::Matrix(int rows, int cols)
    : dx(rows), dy(cols)
{
    numbers = new Num*[dx];
    for (int i = 0; i < dx; ++i) {
        numbers[i] = new Num[dy];
        for (int j = 0; j < dy; ++j) {
            numbers[i][j] = Num(0); // инициализация нулями
        }
    }
}

// Многопоточное умножение
Matrix Matrix::operator*(const Matrix& other) const {
    if (this->dy != other.dx) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    Matrix temp = other.transpond();
    Matrix result(this->dx, other.dy); 

    std::vector<std::thread> threads;
    threads.reserve(this->dx);

    for (int i = 0; i < this->dx; ++i) {
        for (int j = 0; j < other.dy; ++j) {
        threads.emplace_back([&, i, j]() {
                result[i][j] = Matrix::arraySum(Matrix::arrrayMul(this->numbers[i], temp[j], dx), dx);
        });
    }
    }

    for (auto& t : threads) {
        t.join();
    }

    return result;
}


Matrix Matrix::vanillaMul(const Matrix& other) const {
if (this->dx != other.dy) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result;
    result.dy = this->dy;
    result.dx = other.dx;
    result.update(dx, dy);
    result.numbers = new Num*[result.dx];
    for (int i = 0; i < result.dy; ++i) {
        result.numbers[i] = new Num[result.dx];
    }
    //Переделать на транспонирование второго - вроде получше
    for (int i = 0; i < this->dy; ++i) {
            for (int j = 0; j < other.dx; ++j) {
            result.numbers[i][j] = getPartialMul(other, i, j);
            }
}
return result;
}
Num* Matrix::arrrayMul(const Num* array, const Num* otherArray, int len) {
    Num* res = new Num[len];
    std::vector<std::thread> threads;
    for (int i = 0; i < len; ++i) {
        threads.emplace_back([&, i]() {
           res[i] = array[i];
        res[i] = res[i] * otherArray[i]; 
        });
    }
        std::cout << "Total Threads: " << threads.size() << std::endl;
    for (auto& t : threads) {
        t.join();
    }
    return res;
}
Num Matrix::arraySum(const Num* array, int len) {
Num res = array[0];
for (int i = 1; i < len; i++) {
    res = res + array[i];
}
return res;
}