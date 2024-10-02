#pragma once
#include <iostream>
#include <fstream>
#include <vector>
namespace fileInput {
    namespace vector {
       void fstring(std::vector<std::string> &some, std::string filename)
{
    std::ifstream fin;
    fin.open(filename);
    std::string string;
    if (fin.is_open())
    {
        while (fin >> string)
        {
            some.push_back(string);
        }
    }
    fin.close();
}
    }
}