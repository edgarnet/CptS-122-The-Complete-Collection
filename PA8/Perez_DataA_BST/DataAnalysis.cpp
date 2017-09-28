// Edgar Perez
// PA 8 - Data Analysis via BST
#include "DataAnalysis.h"

// Runs the app.
void DataAnalysis::runAnalysis()
{
	openFile();
	if (stream) 
	{
		fileParse(stream);
		trends();
	}
	else 
		std::cout << "We could not open 'myData.csv'" << std::endl;
}

// Prints to the screen trends in the data collected.
void DataAnalysis::trends()
{
	std::cout << std::endl;
	TransactionNode* leastPurchased = mTreePurchased.findSmallest();
	TransactionNode* mostPurchased = mTreePurchased.findLargest();
	TransactionNode* leastSold = mTreesSold.findSmallest();
	TransactionNode* mostSold = mTreesSold.findLargest();
	std::cout << std::endl << "Most Purchased:" << std::endl << "Item: " << mostPurchased->getData() << std::endl << "Units: " << mostPurchased->getUnits() << std::endl;
	std::cout << std::endl << "Most Sold:" << std::endl << "Item: " << mostSold->getData() << std::endl << "Units: " << mostSold->getUnits() << std::endl;
	std::cout << std::endl << "Least Purchased:" << std::endl << "Item: " << leastPurchased->getData() << std::endl << "Units: " << leastPurchased->getUnits() << std::endl;
	std::cout << std::endl << "Least Sold:" << std::endl << "Item: " << leastSold->getData() << std::endl << "Units: " << leastSold->getUnits() << std::endl;
}

// Determines which BST to store a line of data in.
void DataAnalysis::chooseBST(std::string& transaction, std::string& type, int& units)
{
	if (transaction == "Purchased")
		mTreePurchased.insert(type, units);
	else if (transaction == "Sold")
		mTreesSold.insert(type, units);
}

// Loop which collects input as string-streams from data.csv.
void DataAnalysis::fileParse(std::ifstream& newStream)
{
	std::string newLine;
	std::string oldLine;

	getline(newStream, newLine);
	while (newStream)
	{
		int newUnits;
		std::string newType;
		std::string newTransaction;
		getline(newStream, newLine);
		std::istringstream curLine(newLine);
		if (oldLine != newLine)
		{
			streamParse(curLine, newUnits, newType, newTransaction);
			chooseBST(newTransaction, newType, newUnits);
		}
		oldLine = newLine;
	}
	std::cout << "Purchased List:" << std::endl;
	mTreePurchased.inOrderTraversal();
	std::cout << "Sold List:" << std::endl;
	mTreesSold.inOrderTraversal();
}

// Parses information from a string-stream: stored in references.
void DataAnalysis::streamParse(std::istringstream& line, int& units, std::string& type, std::string& transaction)
{
	std::string token;
	getline(line, token, ',');
	std::istringstream(token) >> units;
	getline(line, token, ',');
	std::istringstream(token) >> type;
	getline(line, token, ',');
	std::istringstream(token) >> transaction;
}

// Opens the file with the private ifstream member.
std::ifstream& DataAnalysis::openFile()
{
	stream.open("myData.csv");
	return stream;
}
