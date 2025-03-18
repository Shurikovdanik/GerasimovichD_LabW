#include "IOfile.h"
#include <vector>
#include <string>
#include <fstream>
 
bool IOFileTxt::open(const std::string& fileName, bool isInput = 1) {
	if (isInput) {
		IFile.open(fileName);
		return IFile.is_open();
	}
	else {
		OFile.open(fileName);
		return OFile.is_open();
	}
}
void IOFileTxt::close() {
	if (IFile.is_open()) IFile.close();
	if (OFile.is_open()) OFile.close();
}
std::vector<std::string> IOFileTxt::read(const std::string& fileName) {
	open(fileName);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(IFile, line)) {
		lines.push_back(line);
	}
	close();
	return lines;
}
bool IOFileTxt::write(std::vector<std::string> data, const std::string& fileName) {
	open(fileName, 0);
	for (const auto& line : data) {
		OFile << line << std::endl;
	}
	close();
	return 0;
}
