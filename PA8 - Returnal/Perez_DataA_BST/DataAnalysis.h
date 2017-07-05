// Edgar Perez
// PA 8 - Data Analysis via BST
// Comments in source file.
#pragma once
#include "BST.h"
#include <fstream>
#include <sstream>

class DataAnalysis
{
public:
	DataAnalysis() { ; }
	~DataAnalysis() { ; }
	void runAnalysis();
private:
	BST mTreesSold;
	BST mTreePurchased;
	std::ifstream stream;
	std::ifstream& openFile();
	void streamParse(std::istringstream& line, int& units, std::string& type, std::string& transaction);
	void fileParse(std::ifstream& newStream);
	void chooseBST(std::string& transaction, std::string& type, int& units);
	void trends();
};

