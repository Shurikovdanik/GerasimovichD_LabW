#include "../include/Matrix.h"
#include "../include/Number.h"
#include <vector>
#include <stdexcept>
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
        Num* line = new Num[dx];
        res[i] = line;
    }
    for (int i = 0; i < dy; i++) {
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

// Многопоточное умножение
Matrix Matrix::operator*(const Matrix& other) const {
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
    std::vector<std::thread> threads;
    for (int i = 0; i < this->dy; ++i) {
    
        threads.emplace_back([&, i]() {
            for (int j = 0; j < other.dx; ++j) {
            result.numbers[i][j] = getPartialMul(other, i, j);
            }
        });
}

    for (auto& t : threads) {
        t.join();
    }

    return result;
}
