#include <sstream>
#include "Parser.h"
#include "Repo.h"
#include "Command.h"
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
	std::vector <std::string> code;
	for (int i = 1; i < getData(lines).second - getData(lines).first; i++) {
		std::stringstream temp(lines[i]);
		std::string tempder;
		int tempnum;
		temp >> tempder >> tempnum;
		data.insert({ tempder, tempnum });
	}
	data.insert({ "Ak", 0 });
	for (int i = getData(lines).second - getData(lines).first + 1; i < lines.size() - 1; i++) {
		code.push_back(lines[i]);
		std::stringstream temp(lines[i]);
		std::string curTemp;
		std::string tempCommand;
		
		temp >> tempCommand;
		 Command* ioncr;
		if (tempCommand == "mov")
		{
			(Mov*)ioncr;
			ioncr = new(Mov);
		}
		else if (tempCommand == "add") {
			(Add*) ioncr;
			ioncr = new(Add);
		}
		else if (tempCommand == "sub") {
			(Sub*) ioncr;
			ioncr = new(Sub);
		}
		else if (tempCommand == "mul") {
			(Mul*) ioncr;
			ioncr = new(Mul);
		}
		else if (tempCommand == "div") {
			(Div*) ioncr;
			ioncr = new(Div);
		}
		commands.push_back(ioncr);
		while (temp >> curTemp) {
			if (curTemp == "_") {
				resultKeys.insert(curTemp);
			}
		}

	}

	Repo result(data, commands, resultKeys, code);
	return result;
}
