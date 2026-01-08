#include "Matrix.h"
#include <gtest/gtest.h>
#include <chrono>
using Num = float;

TEST(MatrixTest, Transpose2x3) {
    int dx = 2, dy = 3;
    Num** arr = new Num*[dx];
    for (int i = 0; i < dx; ++i) {
        arr[i] = new Num[dy];
        for (int j = 0; j < dy; ++j) {
            arr[i][j] = i * dy + j + 1; // 1..6
        }
    }

    Matrix m(arr, dx, dy);
    Matrix t = m.transpond();

    EXPECT_EQ(t.getDX(), dy);
    EXPECT_EQ(t.getDY(), dx);

    for (int i = 0; i < dx; ++i) {
        for (int j = 0; j < dy; ++j) {
            EXPECT_EQ(m[i][j], t[j][i]);
        }
    }
}
TEST(MatrixTest, Multiply2x2) {
    int dx = 2, dy = 2;

    Num** a = new Num*[dx];
    Num** b = new Num*[dx];
    for (int i = 0; i < dx; ++i) {
        a[i] = new Num[dy];
        b[i] = new Num[dy];
    }

    // A = [1 2; 3 4]
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    // B = [5 6; 7 8]
    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    Matrix A(a, dx, dy);
    Matrix B(b, dx, dy);

    Matrix C = A * B;

    EXPECT_EQ(C[0][0], 19);
    EXPECT_EQ(C[0][1], 22);
    EXPECT_EQ(C[1][0], 43);
    EXPECT_EQ(C[1][1], 50);
}
TEST(MatrixTest, MultiplyInvalid) {
    int dx = 2, dy = 3;
    Num** a = new Num*[dx];
    Num** b = new Num*[dx];
    for (int i = 0; i < dx; ++i) {
        a[i] = new Num[dy];
        b[i] = new Num[dy];
    }

    Matrix A(a, dx, dy);
    Matrix B(b, dx, dy);

    EXPECT_THROW(A * B, std::invalid_argument);
}
TEST(MatrixTest, Multiply1000x1000) {
    const int size = 1000;

    Num** A = new Num*[size];
    Num** B = new Num*[size];
    for (int i = 0; i < size; ++i) {
        A[i] = new Num[size];
        B[i] = new Num[size];
        for (int j = 0; j < size; ++j) {
            A[i][j] = Num(1);
            B[i][j] = Num(2);
        }
    }

    Matrix mA(A, size, size);
    Matrix mB(B, size, size);

    Matrix result = mA * mB;

    // Проверка нескольких элементов
    EXPECT_EQ(result[0][0], Num(2000)); // 1000 * 2
    EXPECT_EQ(result[size - 1][size - 1], Num(2000));
    EXPECT_EQ(result[size / 2][size / 2], Num(2000));

    // Очистка памяти
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
}
TEST (MatrixTestCompare, Matrix_vanilla){
    const int size = 1000;

    Num** A = new Num*[size];
    Num** B = new Num*[size];
    for (int i = 0; i < size; ++i) {
        A[i] = new Num[size];
        B[i] = new Num[size];
        for (int j = 0; j < size; ++j) {
            A[i][j] = Num(1);
            B[i][j] = Num(2);
        }
    }

    Matrix mA(A, size, size);
    Matrix mB(B, size, size);
    Matrix result = mA.vanillaMul(mB);
  
    // Проверка нескольких элементов
    EXPECT_EQ(result[0][0], Num(2000)); // 1000 * 2
    EXPECT_EQ(result[size - 1][size - 1], Num(2000));
    EXPECT_EQ(result[size / 2][size / 2], Num(2000));

    // Очистка памяти
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
}
TEST (MatrixTestCompare, Matrix_Multithread){
    const int size = 1000;

    Num** A = new Num*[size];
    Num** B = new Num*[size];
    for (int i = 0; i < size; ++i) {
        A[i] = new Num[size];
        B[i] = new Num[size];
        for (int j = 0; j < size; ++j) {
            A[i][j] = Num(1);
            B[i][j] = Num(2);
        }
    }

    Matrix mA(A, size, size);
    Matrix mB(B, size, size);
    Matrix result = mA * mB;
    // Проверка нескольких элементов
    EXPECT_EQ(result[0][0], Num(2000)); // 1000 * 2
    EXPECT_EQ(result[size - 1][size - 1], Num(2000));
    EXPECT_EQ(result[size / 2][size / 2], Num(2000));

    // Очистка памяти
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
}
// --- Тесты для arrrayMul ---
TEST(MatrixHelpersTest, ArrayMulSimple) {
    Num a[3] = {1, 2, 3};
    Num b[3] = {4, 5, 6};

    Num* res = Matrix::arrrayMul(a, b, 3);

    EXPECT_EQ(res[0], 4);   // 1*4
    EXPECT_EQ(res[1], 10);  // 2*5
    EXPECT_EQ(res[2], 18);  // 3*6

    delete[] res; // освобождаем память
}

TEST(MatrixHelpersTest, ArrayMulWithZeros) {
    Num a[4] = {0, 2, 0, 4};
    Num b[4] = {5, 0, 7, 1};

    Num* res = Matrix::arrrayMul(a, b, 4);

    EXPECT_EQ(res[0], 0);   // 0*5
    EXPECT_EQ(res[1], 0);   // 2*0
    EXPECT_EQ(res[2], 0);   // 0*7
    EXPECT_EQ(res[3], 4);   // 4*1

    delete[] res;
}

// --- Тесты для arraySum ---
TEST(MatrixHelpersTest, ArraySumSimple) {
    Num arr[3] = {1, 2, 3};
    Num sum = Matrix::arraySum(arr, 3);

    EXPECT_EQ(sum, 6); // 1+2+3
}

TEST(MatrixHelpersTest, ArraySumWithNegatives) {
    Num arr[5] = {10, -5, 3, -2, 4};
    Num sum = Matrix::arraySum(arr, 5);

    EXPECT_EQ(sum, 10); // 10-5+3-2+4 = 10
}