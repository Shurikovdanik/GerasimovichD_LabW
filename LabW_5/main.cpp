#include <iostream>
#include <fstream>
#include <string>
#include <vector>
void fin (std::vector <std::string> &someStrings, std::string filename)
{
std::ifstream fin;
    fin.open (filename);
    std::string string;
     if (fin.is_open()) {
        while (getline (fin, string)) {
           someStrings.push_back(string);
        }
    }
    fin.close();
}
bool isSame (std::string first, std::string second)
{
    if (first.size() == second.size()) {
        bool isSame = 1;
        for (int i = 0; i < first.size(); i++)
        {
            if (first[i] != second[i]) {
                isSame = 0;
                break;
            }
        }
        return isSame;
    }
    else return 0;
}
int numberOfSame (std::vector <std::string> &someStrings, int begin, int num)
{
    bool isOver = 0;
    int res = 1;
    if (begin + 1 < num) {
    do {
        if (isSame (someStrings[begin], someStrings[begin + 1])) {
            begin++;
            res++;
        }
        else isOver = 1;
    }while (!isOver);
    }
    return res;
}
void fout (std::vector <std::string> &someStrings, int num)
{
    std::ofstream fout;
    std::cout <<std::endl << "Name of output file: ";
    std::string filename = "data/OUTPUT.txt";
    std::cout << filename;
    fout.open(filename);
    for (int i = 0; i < num; ) {
        fout << "Text: " << someStrings[i] <<". Number of repeats: " << numberOfSame(someStrings, i, num) <<   ". Starting from " << i + 1 << " line. " << std::endl;
        i += numberOfSame(someStrings, i, num);
    }
    fout.close();
}
int main ()
{
std::cout << "File name of input: ";
std::string filename = "data/INPUT.txt";
std::cout << filename;
std::vector <std::string> someStrings;
fin (someStrings, filename);
int numberOfElements = someStrings.size();
fout (someStrings, numberOfElements);
}