#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace input { //ввод
    template <typename some>
    void fin (some* array,  std::string filename) { // Обобщённый ввод динамического массива с файла (приписка в конец)
        std::ifstream fin;
    fin.open (filename);
    some string;
    unsigned long long size = 0;
     if (fin.is_open()) {
        while (fin >> string) {
          array = (int*)realloc(array, sizeof(int) * (++size));
          array[i] = string;
        }
    }
    fin.close();
    }
    template <typename some>
   void finVector (std::vector <some&> array,  std::string filename) //Обобщённый ввод вектора с файла(приписка в конец)
{
   std::ifstream fin;
    fin.open (filename);
    std::string string;
     if (fin.is_open()) {
        while (fin >> string) {
           array.push_back(string);
        }
    }
    fin.close();
}
    template <typename some>
    void cin (some* array, int num) { //Обобщённый ввод массива с клавиатуры(приписка в конец)
for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
unsigned long long size = 0;
    array = (int*)realloc(array, sizeof(int) * (++size));
    std::cin >> array[i];
}
}
    template <typename some>
    void cinVector (std::vector <some&> &array, int num) { //Обобщённый клавиатурный ввод вектора (приписка в конец)
        for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
unsigned long long size = 0;
    some temp;
    std::cin >> temp;
    array.push_back(temp);
}
    }
    template <typename some>
    void rand (some array, some& lowLimit, some& upLimit, int num) { //Случайная генерация обобщённого вектора в заданном диапозоне
        for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        temp = rand () % (upLimit - lowLimit) + lowLimit;
     array = (int*)realloc(array, sizeof(int) * (++size));
     a[i] = temp;
    }
    }
    
   template <typename some>
    void randVector (std::vector <some&> &array,  some& lowLimit, some& upLimit, int num) { //Случайная генерация обобщённого вектора в заданном диапозоне
 for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        temp = rand () % (upLimit - lowLimit) + lowLimit;
    array.push_back(temp);
    }
    }
}
namespace output { //вывод 
    template <typename some>
    void fout (some* array,  std::string filename) { //вывод в файл
        std::ofstream fout;
    fout.open (filename);
    some string;
     if (fout.is_open()) {
        for (int i = 0; i < sizeof(array) / sizepf(array[0]); i++) {
          fout << arrai[i] << "\t";
        }
    }
    fout.close();
    }
    template <typename some>
    void foutVector (std::vector <some&> &array,  std::string filename) { //вывод вуктора в файл
         std::ofstream fout;
    fout.open (filename);
    some string;
     if (fout.is_open()) {
        for (int i = 0; i < array.size(); i++) {
          fout << arrai[i] << "\t";
        }
    }
    fout.close();
    }
    template <typename some>
    void cout (some array*, int num) { //вывод массива на консоль
        for (int i = 0; i < sizeof(array) + 1; i++)
        {
            std::cout << array[i] << "\t";
        }
    }
    template <typename some>
    void coutVector (std::vector <some&> &array, int num) { //вывод вектора на консоль
    for (int i = 0; i < array.size(); i++)
        {
            std::cout << array[i] << "\t";
        }
    }
}
namespace fromFileAriphmetics {
    int size (std::string filename); //размер массива из файла
}
namespace ariphmetics {
    unsigned int gcd (unsigned int first,unsigned int second); //НОД двух натуральных французских
}
