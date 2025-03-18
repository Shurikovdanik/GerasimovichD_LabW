#include <sstream>
#include "Parser.h"
#include "Repo.h"

std::pair<Parser::VIt, Parser::VIt> Parser::getData(std::vector<std::string>& lines) {
    auto start = std::find(lines.begin(), lines.end(), ".data");
    auto end = std::find(start, lines.end(), ".code");
    return { start, end };
}

std::pair<Parser::VIt, Parser::VIt> Parser::getCode(std::vector<std::string>& lines) {
    auto start = std::find(lines.begin(), lines.end(), ".code");
    auto end = std::find(start, lines.end(), "end");
    return { start, end };
}
Repo Parser::interpretate(std::vector<std::string> lines) {

	std::map<std::string, int> data;
	std::vector <Command*> commands;
	std::set<std::string> resultKeys;
	for (int i = 0; i < getData(lines).second - getData(lines).first; i++) {
		std::stringstream temp(lines[i]);
		std::string tempder;
		int tempnum;
		temp >> tempder >> tempnum;
		data.insert({ tempder, tempnum });
	}
	for (int i = 0; i < getCode(lines).second - getCode(lines).first; i++) {
		std::stringstream temp(lines[i]);
		std::string curTemp;
		std::string tempCommand;
		temp >> tempCommand;
		Command* ioncr;
		commands.push_back(ioncr);
		while (temp >> curTemp) {
			resultKeys.insert(curTemp);
		}

	}
	Repo result(data, commands, resultKeys);
	return result;
}
