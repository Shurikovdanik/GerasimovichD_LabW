#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <array>
#include "basicactions.h"
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
std::stringstream input::finStreamString ( std::string fileName) {
        std::stringstream res;
        std::ifstream fin(fileName);
        if (fin.is_open()) {   
    char buffer[MAX_BUFFER];
    while (fin)     
    {
        fin.getline(buffer, MAX_BUFFER);
        res << buffer << " ";
    }
    }
    return res;
    }

