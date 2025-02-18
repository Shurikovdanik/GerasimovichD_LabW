#pragma once
#include "Repo.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include "Command.h"

class Repo {
private:
	std::map<std::string, int> data;
	std::vector <Command*> commands;
	std::vector <std::string> code;
	std::set<std::string> resultKeys;
public:
	Repo(std::map<std::string, int> data, std::vector <Command*> commands, std::set<std::string> resultKeys, std::vector <std::string>& code) {
		this->data = data;
		this ->commands = commands;
		this->resultKeys = resultKeys;
		this->code = code;
	}
	void execCode();
};
