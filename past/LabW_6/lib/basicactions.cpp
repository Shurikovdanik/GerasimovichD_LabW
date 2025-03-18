#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "..\headers\basicactions.h"
#pragma once
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


