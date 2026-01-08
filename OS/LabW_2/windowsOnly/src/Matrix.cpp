#include "../include/Matrix.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
using Num = float;
CRITICAL_SECTION CS;
Matrix::Matrix(Num** given, unsigned int dx,unsigned int dy)
    : numbers(given)
{
    this->dx = dx;
    this->dy = dy;
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
struct ThreadData {
    const Matrix* A;
    const Matrix* B_transposed;
    Matrix* result;
    int tid;
    int nthreads;
};



DWORD WINAPI worker(LPVOID param) {
    
    ThreadData* data = static_cast<ThreadData*>(param);
    const Matrix* A = data->A;
    const Matrix* B = data->B_transposed;
    Matrix* result = data->result;
    int tid = data->tid;
    int nthreads = data->nthreads;

    int tiles_rows = (A->dx + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int tiles_cols = (B->dx + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int total_tiles = tiles_rows * tiles_cols;

    int tiles_per_thread = (total_tiles + nthreads - 1) / nthreads;
    int start_tile = tid * tiles_per_thread;
    int end_tile = std::min(start_tile + tiles_per_thread, total_tiles);

    for (int tile_idx = start_tile; tile_idx < end_tile; ++tile_idx) {
        int ti = tile_idx / tiles_cols;
        int tj = tile_idx % tiles_cols;

        int row_start = ti * BLOCK_SIZE;
        int row_end = std::min(row_start + BLOCK_SIZE, A->dx);
        int col_start = tj * BLOCK_SIZE;
        int col_end = std::min(col_start + BLOCK_SIZE, B->dx);

        for (int i = row_start; i < row_end; ++i) {
            for (int j = col_start; j < col_end; ++j) {
                Num sum = 0.0f;
                for (int k = 0; k < A->dy; ++k) {
                    sum += A->numbers[i][k] * B->numbers[j][k];
                }

                EnterCriticalSection(&CS);
                result->numbers[i][j] = sum;
                LeaveCriticalSection(&CS);
            }
        }
    }

    return 0;
}


Matrix Matrix::operator*(const Matrix& other) const {
    if (dy != other.dx) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    Matrix result(dx, other.dy);
    Matrix temp = other.transpond();

    unsigned nthreads = std::thread::hardware_concurrency();
    HANDLE* handles = new HANDLE[nthreads];
    ThreadData* threadData = new ThreadData[nthreads];
    InitializeCriticalSection(&CS);

    for (unsigned t = 0; t < nthreads; ++t) {
        threadData[t] = { this, &temp, &result, static_cast<int>(t), static_cast<int>(nthreads) };
        handles[t] = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)worker, &threadData[t], 0, nullptr);
    }

    WaitForMultipleObjects(nthreads, handles, TRUE, INFINITE);

    for (unsigned t = 0; t < nthreads; ++t) {
        CloseHandle(handles[t]);
    }
    DeleteCriticalSection(&CS);

    delete[] handles;
    delete[] threadData;

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