#include "../include/Matrix.h"
#include "../include/Number.h"
#include <vector>
#include <stdexcept>
#include <iostream>
using Num = float;
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



Num Matrix::getPartialMul(const Matrix& other, int i, int j) const {
    Num sum = 0;
    for (int k = 0; k < dx; ++k) {
        sum = sum + (this->numbers[i][k] * other.numbers[k][j]);
    }
    return sum;
}


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
    if (dy != other.dx) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(dx, other.dy);
    Matrix temp = other.transpond();

    unsigned nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(nthreads);

    auto worker = [&](int tid) {
        for (int ii = tid * BLOCK_SIZE; ii < dx; ii += nthreads * BLOCK_SIZE) {
            for (int jj = 0; jj < other.dy; jj += BLOCK_SIZE) {
                for (int kk = 0; kk < dy; kk += BLOCK_SIZE) {
                    for (int i = ii; i < std::min(ii + BLOCK_SIZE, dx); ++i) {
                        for (int j = jj; j < std::min(jj + BLOCK_SIZE, other.dy); ++j) {
                            Num sum = result[i][j];
                            for (int k = kk; k < std::min(kk + BLOCK_SIZE, dy); ++k) {
                                sum = sum + this->numbers[i][k] * temp.numbers[j][k];
                            }
                            result[i][j] = sum;
                        }
                    }
                }
            }
        }
    };

    for (unsigned t = 0; t < nthreads; ++t) {
        threads.emplace_back(worker, t);
    }
    for (auto &th : threads) {th.join();}

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