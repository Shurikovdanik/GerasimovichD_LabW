#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
namespace input {
    template <typename T>
    void rand (T *array, T& lowLimit, T& upLimit, int num) {
        for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        temp = rand () % (upLimit - lowLimit) + lowLimit;
     array = (int*)realloc(array, sizeof(int) * (++size));
     a[i] = temp;
    }
    }
   template <typename T>
    void randVector (std::vector <T&> &array,  T& lowLimit, T& upLimit, int num) {
 for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        temp = rand () % (upLimit - lowLimit) + lowLimit;
    array.push_back(temp);
    }
    }
}
namespace output {
}
namespace arrayAriphmetics {
    template <typename T>
    T sumOfVector (std::vector <T> &vector) {
        T res = vector[0];
        for (int i = 1; i < vector.size();i++) {
            res += vector[i];
        }
        return res;
    }
    template <typename T>
     T sumOfArray (T *array) {
        T res = array[0];
        for (int i = 1; i < sizeof(array) / sizeof(array[0]);i++) {
            res += vector[i];
        }
        return res;
    }
    template <typename T, size_t num>
     T sumOfArray (std::array <T, num> array) {
        T res = array[0];
        for (int i = 1; i < num;i++) {
            res += array[i];
        }
        return res;
    }
}
namespace fromFileAriphmetics {
    int size (std::string filename);
}
namespace ariphmetics {
    unsigned int gcd (unsigned int first,unsigned int second);
}
//TODO: переделать