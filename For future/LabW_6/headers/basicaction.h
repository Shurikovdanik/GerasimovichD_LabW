#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace input {
    template <typename some>
    void fin (some array,  std::string filename);
    template <typename some>
    void finVector (std::vector <some&> &array,  std::string filename);
    template <typename some1>
    void cin (some1 *array, int num);
    template <typename some>
    void cinVector (std::vector <some&> &array, int num);
    template <typename some>
    void rand (some array, some& lowLimit, some& upLimit, int num);
    template <typename some>
    void randVector (std::vector <some&> &array,  some& lowLimit, some& upLimit, int num);
}
namespace output {
    template <typename some>
    void fout (some array,  std::string filename);
    template <typename some>
    void foutVector (std::vector <some&> &array,  std::string filename);
    template <typename some>
    void cout (some array, int num);
    template <typename some>
    void coutVector (std::vector <some&> &array, int num);
}
namespace fromFileAriphmetics {
    int size (std::string filename);
}
namespace ariphmetics {
    unsigned int gcd (unsigned int first,unsigned int second);
}
