#pragma once
#include <vector>
#include <string>
#include "Repo.h"
class Parser
{
private:
	typedef std::vector<std::string>::iterator VIt;
public:
	std::pair<VIt, VIt> getData(std::vector<std::string>&);
	std::pair<VIt, VIt> getCode(std::vector<std::string>&);
	Repo interpretate(std::vector<std::string> lines);
};
