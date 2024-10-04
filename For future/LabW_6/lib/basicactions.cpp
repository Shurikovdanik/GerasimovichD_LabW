#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "../headers/basicaction.h"
    template <typename some>
    void input::fin (some array,  std::string filename) {
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
void finVector (std::vector <some&> array,  std::string filename)
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
void input::cin (some* array, int num) {
for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
unsigned long long size = 0;
    array = (int*)realloc(array, sizeof(int) * (++size));
    std::cin >> array[i];
}
}
    template <typename some>
    void input::cinVector (std::vector <some&> &array, int num) {
        for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        std::cin >> temp;
    array.push_back(temp);
}
    }
    template <typename some>
    void input::rand (some array, some& lowLimit, some& upLimit, int num) {
        unsigned long long size = 0;
for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
    array = (int*)realloc(array, sizeof(int) * (++size));
    array[i] = rand () % upLimit + lowLimit;
}
    }
    template <typename some>
    void input::randVector (std::vector <some&> &array,  some& lowLimit, some& upLimit, int num) {
 for (int i = sizeof(array) + 1; i < num + sizeof(array) + 1; i++) {
        some temp;
        std::cin >> temp;
    array.push_back(temp);
    }
    }
template <typename some>
    void output::fout (some array,  std::string filename) {
        std::ofstream fout;
    fout.open (filename);
    some string;
     if (fout.is_open()) {
        for (int i = 0; i < sizeof(array); i++) {
          fout << arrai[i] << "\t";
        }
    }
    fout.close();
    }
    template <typename some>
    void output::foutVector (std::vector <some&> &array,  std::string filename) {
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
    void output::cout (some array, int num) {
        for (int i = 0; i < sizeof(array) + 1; i++)
        {
            std::cout << array[i] << "\t";
        }
    }
    template <typename some>
    void output::coutVector (std::vector <some&> &array, int num) {
    for (int i = 0; i < array.size(); i++)
        {
            std::cout << array[i] << "\t";
        }
    }
    int fromFileAriphmetics::size (std::string filename) {
        int res = 0;
        std::ifstream fin;
    fin.open (filename);
    std::string string;
     if (fin.is_open()) {
        while (fin >> string) {
           res++;
        }
    }
    fin.close();
    return res;
    }
    unsigned int ariphmetics::gcd (unsigned int first, unsigned int second) {
        while (first != second) {
            if (first > second) {
                first = first - second;
            }
            else {
                second = second - first;
            }
        }
        return first;
    }


