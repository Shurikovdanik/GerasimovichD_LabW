#pragma once
#include <vector>
#include <string>
#include <fstream>
class IOFile {
public:
	virtual bool open(const std::string& fileName, bool isInput) = 0;
	virtual void close() = 0;
	virtual std::vector<std::string> read(const std::string&) = 0;
	virtual bool write(std::vector<std::string>, const std::string&) = 0;
};

class IOFileTxt : IOFile {
private:
	std::ifstream IFile;
	std::ofstream OFile;
public:
	virtual bool open(const std::string& fileName, bool isInput);
	virtual void close();
	virtual std::vector<std::string> read(const std::string&);
	virtual bool write(std::vector<std::string>, const std::string&);
};
class IOFileJson : IOFile {
	
};
