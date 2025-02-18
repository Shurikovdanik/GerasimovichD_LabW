#include "Repo.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include "Command.h"
void Repo::execCode() {
 
    for (int i = 0; i < commands.size(); i++) {
        std::vector <int> num;
        std::vector <std::string> keys;
        for (int j = 0; j < 3; j++) {
            num.push_back(0);
      }
        std::stringstream temp(code[i]);
        std::string curTemp;
        temp >> curTemp;
        int j = 0;
        std::stringstream revTemp;
        while (temp >> curTemp) {
            num[j] = data[curTemp];
            keys.push_back(curTemp);
            j++;  
        }
        //std::cout << num[0] << " " << num[1] << std::endl;
        if (j < 2) {
            num[2] = num[0];
            num[0] = num[1];
            num[1] = num[2];
        }
       // else if (j == 2) {
         //   int boo = num[2];
        //    num[2] = num[0];
       //     num[0] = boo;
       // }
        //std::cout << curTemp << std::endl;
        commands[i]->exec(num[0], num[1], num[2]);
        //std::cout << keys[0] << " ";
        data[keys[0]] = num[0];
        for (auto curr : data) {
           std::cout << curr.first << " " << curr.second << std::endl;
        }
    }
    
}