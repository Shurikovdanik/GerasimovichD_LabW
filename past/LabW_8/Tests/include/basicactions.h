#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include "..\pch.h"
const unsigned int MAX_BUFFER = 300;
namespace input {
    template <typename T>
    void streamInputVector (std::vector <T> &array, std::istream &stream) {
        T temp;
        while (stream >> temp) {
            array.push_back(temp);
        }
    }
    template <typename T>
    void streamInputArray (T* array, std::istream &stream) {
        T temp;
        while (stream >> temp) {
        array = realloc(array, sizeof(array) + sizeof(T));    
        }
    }
    template <typename T, size_t num>
    void streamInputArray(std::array <T, num> &array, std::istream &stream) {
         for (int i = 0; i < num; i++) {
            stream >> array[i];
        }
    }
    template <typename T>
    void rand (T *array, T& lowLimit, T& upLimit, int num) {
        for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        T temp;
        temp = std::rand () % (upLimit - lowLimit) + lowLimit;
     array = (int*)realloc(array, sizeof(int) * (++(sizeof(array) / sizeof(int))));
     array[i] = temp;
    }
    }
   template <typename T>
    void randVector (std::vector <T&> &array,  T& lowLimit, T& upLimit, int num) {
 for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        T temp;
        temp = std::rand () % (upLimit - lowLimit) + lowLimit;
    array.push_back(temp);
    }
    }
    std::stringstream finStreamString (std::string fileName);
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
            res += array[i];
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
    template <typename T>
    unsigned int count (const T* array,const T looked) {
        unsigned int counter = 0;
        for (int i = 0; i < sizeof(array) / sizeof(T); i++) {
            if(array[i] == looked) {
                counter++;
            }
        }
        return counter;
    }
    template <typename T, typename U>
    int findFirstLooked (T array, U looked, int num) { //Для одинаковой работоспособности для вектора и массива
        
        for (int i = 0; i < num; i++) {
           if(array[i] == looked) {
                return i;
              
            }
        }
       throw std::exception ("No such element.");
    }
    template <typename T, typename U>
    int findLastLooked (T array, U looked, int num) {
        for (int i = num - 1; i >= 0; i--) {
           if(array[i] == looked) {
                return i;
            }
        }
       throw std::exception ("No such element.");
    }
}
namespace fromFileAriphmetics {
    int size (std::string filename);
}
namespace ariphmetics {
    unsigned int gcd (unsigned int first,unsigned int second);
}
//TODO: переделать