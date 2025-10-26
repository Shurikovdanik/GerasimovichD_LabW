#include "../include/Matrix.h"
#include "../include/Number.h"
#include "ThreadTunnel.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <mutex>

using Num = float;
Matrix::Matrix(Num **given, unsigned int dx, unsigned int dy)
    : numbers(given)
{
    // TODO: measures
    dx = dx;
    dy = dy;
}
void Matrix::update(int dx, int dy)
{
    this->dx = dx;
    this->dy = dy;
}

bool Matrix::isSameSize(const Matrix &other) const
{
    return (this->dx == other.dx && this->dy == other.dy);
}

Matrix Matrix::transpond() const
{
    Num **res = new Num *[dx];
    for (int i = 0; i < dy; i++)
    {
        res[i] = new Num[dx];
        for (int j = 0; j < dx; j++)
        {
            res[i][j] = numbers[j][i];
        }
    }
    return Matrix(res, dy, dx);
}

Num Matrix::getPartialMul(const Matrix &other, int i, int j) const
{
    Num sum = 0;
    for (int k = 0; k < dx; ++k)
    {
        sum = sum + (this->numbers[i][k] * other.numbers[k][j]);
    }
    return sum;
}

Num *Matrix::getMulLines(const Matrix &other, int i) const
{
    Num *row = new Num[other.dx];
    for (int j = 0; j < other.dx; ++j)
    {
        row[j] = getPartialMul(other, i, j);
    }
    return row;
}
Matrix::Matrix(int rows, int cols)
    : dx(rows), dy(cols)
{
    numbers = new Num *[dx];
    for (int i = 0; i < dx; ++i)
    {
        numbers[i] = new Num[dy];
        for (int j = 0; j < dy; ++j)
        {
            numbers[i][j] = Num(0); // инициализация нулями
        }
    }
}

// Многопоточное умножение
Matrix Matrix::operator*(const Matrix &other) const {
    if (dy != other.dx) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(dx, other.dy);
    Matrix temp = other.transpond();

    using Task = std::tuple<int,int>; 
    ThreadTunnel<Task> tunnel;
    std::mutex result_mutex;
    for (int i = 0; i < std::thread::hardware_concurrency() * 1.0; i++) {
        tunnel.addThread("Thread" + std::to_string(i), [&](const Task& task) {
        auto [ti, tj] = task;
        int rowStart = ti * BLOCK_SIZE;
        int colStart = tj * BLOCK_SIZE;
        for (int i = rowStart; i < std::min(rowStart + BLOCK_SIZE, dx); i++) {
            for (int j = colStart; j < std::min(colStart + BLOCK_SIZE, other.dy); j++) {
                Num sum = Num(0);
                for (int k = 0; k < dy; ++k) {
                    sum = sum + this->numbers[i][k] * temp.numbers[j][k];
                }
                std::lock_guard<std::mutex> lock(result_mutex);
                result[i][j] += sum;
            }
        }
    });
}   //Нужна оптимизация на добавление в очередь
    for (int ti = 0; ti < (dx + BLOCK_SIZE - 1) / BLOCK_SIZE; ++ti) {
        for (int tj = 0; tj < (other.dy + BLOCK_SIZE - 1) / BLOCK_SIZE; ++tj) {
            tunnel.send(std::make_tuple(ti, tj));
        }
    }
    //В туннеле нужно по ивентам бы
    std::this_thread::sleep_for(std::chrono::milliseconds(10 * dx / std::thread::hardware_concurrency()));

    return result;
}

Matrix Matrix::vanillaMul(const Matrix &other) const
{
    if (this->dx != other.dy)
    {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result;
    result.dy = this->dy;
    result.dx = other.dx;
    result.update(dx, dy);
    result.numbers = new Num *[result.dx];
    for (int i = 0; i < result.dy; ++i)
    {
        result.numbers[i] = new Num[result.dx];
    }
    for (int i = 0; i < this->dy; ++i)
    {
        for (int j = 0; j < other.dx; ++j)
        {
            result.numbers[i][j] = getPartialMul(other, i, j);
        }
    }
    return result;
}
Num *Matrix::arrrayMul(const Num *array, const Num *otherArray, int len)
{
    Num *res = new Num[len];
    std::vector<std::thread> threads;
    for (int i = 0; i < len; ++i)
    {
        threads.emplace_back([&, i]()
                             {
           res[i] = array[i];
        res[i] = res[i] * otherArray[i]; });
    }
    std::cout << "Total Threads: " << threads.size() << std::endl;
    for (auto &t : threads)
    {
        t.join();
    }
    return res;
}
Num Matrix::arraySum(const Num *array, int len)
{
    Num res = array[0];
    for (int i = 1; i < len; i++)
    {
        res = res + array[i];
    }
    return res;
}
std::string Matrix::toString() const
{
    std::ostringstream oss;
    oss << "Matrix(" << dx << "x" << dy << "):\n";
    for (int i = 0; i < dx; ++i)
    {
        oss << "[ ";
        for (int j = 0; j < dy; ++j)
        {
            oss << std::setw(8) << numbers[i][j] << " ";
        }
        oss << "]\n";
    }
    return oss.str();
}